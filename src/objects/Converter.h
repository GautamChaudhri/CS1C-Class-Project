//Converter.h
#ifndef CONVERTER_H
#define CONVERTER_H
#include <iostream>
#include <cctype>
#include "shapes/all_shapes.h"
#include "vector.h"

//enum QObjects {QPen, QBrush, QPoint, QString, QFont};

struct MorphicShape {
    std::string shapeType = "";
    int shapeId = -1;
    int trackerId = -1;
    alpha::vector<int> shapeDimensions;
    //alpha::vector<QPoint> dimensionPoints;
    QPen pen = QPen();
    QBrush brush = QBrush();
    QPoint coords;

    QString textString;
    GlobalColor textColor;
    QFont font;
    AlignmentFlag textAlignment;
};

class Converter {
public:
    alpha::vector<Shape*> parseJson(const std::string& json) {
        alpha::vector<Shape*> shapes;
        Shape* newShape = nullptr;

        size_t index = 0;   //index at [
        if (json[index] != '[')
            throw std::runtime_error("Expected '[' at the beginning of string.");
        else
            index++;
        SkipWhitespace(json, index);

        while (true) {
            SkipWhitespace(json, index);
            if (json[index] == ']')
                break;
            
            MorphicShape tempShape = ParseJsonObject(json, index);

            newShape = BuildShape(tempShape);
            shapes.push_back(newShape);

            SkipWhitespace(json, index);
            if(json[index] == ',')
                index++;
            else if (json[index] == ']')
                break;
            else
                throw std::runtime_error("Expected ',' or ']'.");
        }
        return shapes;
    }

private: 
    MorphicShape ParseJsonObject(const std::string json, size_t &index) {
        //index at {
        MorphicShape tempShape;

        if (json[index] != '{')
            throw std::runtime_error("Expected '{'.");
        else
            index++;
        SkipWhitespace(json, index);

        while(true) {
            SkipWhitespace(json, index);
            if (json[index] == '}') {
                index++;
                break;
            }

            if (json[index] != '"')
                throw std::runtime_error("Expected '\"'.");

            std::string key = ExtractKey(json, index);
            SkipWhitespace(json, index);

            if (json[index] != ':')
                throw std::runtime_error("Expected ':'.");
            index++;
            SkipWhitespace(json, index);    //index at value

            std::string value = ExtractValue(json, index);
            SkipWhitespace(json, index);

            //add values to tempShape
            UpdateMorphicShape(key, value, tempShape);

            if (json[index] == ',') {       //if comma, loop again
                index++;
                SkipWhitespace(json, index);
            }
            else if (json[index] == '}')    //if }, then end of object and break
                break;
            else                            //otherwise invalid json string
                throw std::runtime_error("Expected '}' or ','.");
        }
        return tempShape;
    }

    std::string ExtractKey(const std::string& json, size_t &index) {
        //index at opening "
        size_t closingQuoteIndex = json.find('"', index + 1);   //searching for closing "
        size_t keyLength = closingQuoteIndex - index - 1;
        std::string key = json.substr(index + 1, keyLength);
        index = closingQuoteIndex + 1;
        return key;
    }

    std::string ExtractValue(const std::string& json, size_t &index) {
        //index at value
        std::string value;

        if (json[index] == '"')             //value is a string so extraction process is the same as ExtractKey()
            value = ExtractKey(json, index);
        else if (isdigit(json[index]))      //value is a number
            value = ExtractInteger(json, index);
        else if (json[index] == '[')        //value is an array
            value = ExtractArray(json, index);
        else if (json[index] == 'n')        //value is null
            value = ExtractNull(json, index);
        else
            throw std::runtime_error("Expected '\"', '[', integer, or null.");
        
        return value;
    }

    std::string ExtractInteger(const std::string& json, size_t &index) {
        size_t startIndex = index;
        while (isdigit(json[index]))
            index++;
        
        std::string integerStr = json.substr(startIndex, index - startIndex);
        return integerStr;
    }

    std::string ExtractArray(const std::string& json, size_t &index) {
        size_t closingBracketIndex = json.find(']', index + 1);
        if (closingBracketIndex == std::string::npos) {
            throw std::runtime_error("Missing ']' in array");
        }
        std::string arrayStr = json.substr(index, closingBracketIndex + 1);
        index = closingBracketIndex + 1;
        return arrayStr;
    }

    std::string ExtractNull(const std::string& json, size_t &index) {
        std::string nullStr = json.substr(index, 4);
        index += 4;
        if (nullStr != "null")
            throw std::runtime_error("Expected null");
        return nullStr;
    }

    void SkipWhitespace(const std::string& json, size_t& index) {
        while (index < json.length() && isspace(json[index])) {
            ++index;
        }
    }

    void UpdateMorphicShape(const std::string &key, const std::string &value, MorphicShape &tempShape) {
        if (key == "ShapeId") {
            tempShape.shapeId = std::stoi(value);
        }
        else if (key == "TrackerId") {
            tempShape.trackerId = std::stoi(value);
        }
        else if (key == "ShapeType") {
            tempShape.shapeType = value;
        }
        else if (key == "ShapeDimensions") {
            alpha::vector<int> dimensions = StringToVector(value);
        }
        else if (key == "PenWidth") {
            int width = std::stoi(value);
            if (width < 0 || width > 12)
                throw std::runtime_error("Invalid pen width: " + value);
            else 
                tempShape.pen.setWidth(width);
        }
        else if (key == "PenColor") {
            if (value == "red")
                tempShape.pen.setColor(Qt::red);
            else if (value == "green")
                tempShape.pen.setColor(Qt::green);
            else if (value == "yellow")
                tempShape.pen.setColor(Qt::yellow);
            else if (value == "cyan")
                tempShape.pen.setColor(Qt::cyan);
            else if (value == "magenta")
                tempShape.pen.setColor(Qt::magenta);
            else if (value == "gray")
                tempShape.pen.setColor(Qt::gray);
            else if (value == "blue")
                tempShape.pen.setColor(Qt::darkGray);
            else if (value == "black")
                tempShape.pen.setColor(Qt::lightGray);
            else if (value == "transparent")
                tempShape.pen.setColor(Qt::transparent);
            else
                throw std::runtime_error("Unknown color: " + value);
        }
        else if (key == "PenStyle") {
            if (value == "SolidLine")
                tempShape.pen.setStyle(Qt::SolidLine);
            else if (value == "DashLine")
                tempShape.pen.setStyle(Qt::DashLine);
            else if (value == "DotLine")
                tempShape.pen.setStyle(Qt::DotLine);
            else if (value == "DashDotLine")
                tempShape.pen.setStyle(Qt::DashDotLine);
            else if (value == "DashDotDotLine")
                tempShape.pen.setStyle(Qt::DashDotDotLine);
            else
                throw std::runtime_error("Unknown pen style: " + value);
        }
        else if (key == "PenCapStyle") {
            if (value == "FlatCap")
                tempShape.pen.setCapStyle(Qt::FlatCap);
            else if (value == "SquareCap")
                tempShape.pen.setCapStyle(Qt::SquareCap);
            else if (value == "RoundCap")
                tempShape.pen.setCapStyle(Qt::RoundCap);
            else
                throw std::runtime_error("Unknown pen cap style: " + value);
        }
        else if (key == "PenJoinStyle") {
            if (value == "MiterJoin")
                tempShape.pen.setJoinStyle(Qt::MiterJoin);
            else if (value == "BevelJoin")
                tempShape.pen.setJoinStyle(Qt::BevelJoin);
            else if (value == "RoundJoin")
                tempShape.pen.setJoinStyle(Qt::RoundJoin);
            else
                throw std::runtime_error("Unknown pen join style: " + value);
        }
        else if (key == "BrushColor") {
            if (value == "red")
                tempShape.brush.setColor(Qt::red);
            else if (value == "green")
                tempShape.brush.setColor(Qt::green);
            else if (value == "yellow")
                tempShape.brush.setColor(Qt::yellow);
            else if (value == "cyan")
                tempShape.brush.setColor(Qt::cyan);
            else if (value == "magenta")
                tempShape.brush.setColor(Qt::magenta);
            else if (value == "gray")
                tempShape.brush.setColor(Qt::gray);
            else if (value == "blue")
                tempShape.brush.setColor(Qt::darkGray);
            else if (value == "black")
                tempShape.brush.setColor(Qt::lightGray);
            else if (value == "transparent")
                tempShape.brush.setColor(Qt::transparent);
            else
                throw std::runtime_error("Unknown color: " + value);
        }
        else if (key == "BrushStyle") {
            if (value == "SolidPattern")
                tempShape.brush.setStyle(Qt::SolidPattern);
            else if (value == "VerPattern")
                tempShape.brush.setStyle(Qt::VerPattern);
            else if (value == "HorPattern")
                tempShape.brush.setStyle(Qt::HorPattern);
            else if (value == "NoBrush")
                tempShape.brush.setStyle(Qt::NoBrush);
            else
                throw std::runtime_error("Unknown brush style: " + value);
        }
        else if (key == "TextString") {
            tempShape.textString = QString::fromStdString(value);
        }
        else if (key == "TextPointSize") {
            int pointSize = std::stoi(value);
            if (pointSize < 0 || pointSize > 100)
                throw std::runtime_error("Invalid point size: " + value);
            else 
                tempShape.font.setPointSize(pointSize);
        }
        else if (key == "TextColor") {
            if (value == "red")
                tempShape.textColor = Qt::red;
            else if (value == "green")
                tempShape.textColor = Qt::green;
            else if (value == "yellow")
                tempShape.textColor = Qt::yellow;
            else if (value == "cyan")
                tempShape.textColor = Qt::cyan;
            else if (value == "magenta")
                tempShape.textColor = Qt::magenta;
            else if (value == "gray")
                tempShape.textColor = Qt::gray;
            else if (value == "blue")
                tempShape.textColor = Qt::darkGray;
            else if (value == "black")
                tempShape.textColor = Qt::lightGray;
            else if (value == "transparent")
                tempShape.textColor = Qt::transparent;
            else
                throw std::runtime_error("Unknown color: " + value);
        }
        else if (key == "TextAlignment") {
            if (value == "AlignLeft")
                tempShape.textAlignment = Qt::AlignLeft;
            else if (value == "AlignRight")
                tempShape.textAlignment = Qt::AlignRight;
            else if (value == "AlignCenter")
                tempShape.textAlignment = Qt::AlignCenter;
            else
                throw std::runtime_error("Unknown text alignment: " + value);
        }
        else if (key == "TextFontFamily") {
            if (value == "Comic Sans MS")
                tempShape.font.setFamily("Comic Sans MS");
            else if (value == "Arial")
                tempShape.font.setFamily("Arial");
            else if (value == "Courier")
                tempShape.font.setFamily("Courier");
            else if (value == "Times")
                tempShape.font.setFamily("Times");
            else
                throw std::runtime_error("Unknown font family: " + value);
        }
        else if (key == "TextFontStyle") {
            if (value == "Normal")
                tempShape.font.setStyle(QFont::StyleNormal);
            else if (value == "Italic")
                tempShape.font.setStyle(QFont::StyleItalic);
            else if (value == "Oblique")
                tempShape.font.setStyle(QFont::StyleOblique);
            else
                throw std::runtime_error("Unknown font style: " + value);
        }
        else if (key == "TextFontWeight") {
            if (value == "Normal")
                tempShape.font.setWeight(QFont::Normal);
            else if (value == "Bold")
                tempShape.font.setWeight(QFont::Bold);
            else if (value == "Light")
                tempShape.font.setWeight(QFont::Light);
            else
                throw std::runtime_error("Unknown font weight: " + value);
        }
        else
            throw std::runtime_error("Unknown key: " + key);
    }

    alpha::vector<int> StringToVector(const std::string &value) {
        //beginning of value is [
        //end of value is ]
        alpha::vector<int> dimensions;
        size_t start = 1;
        SkipWhitespace(value, start);
        while (start < value.length() && value[start] != ']') {
            size_t end = value.find(',', start);
            if (end == std::string::npos || end > value.length()) {
                end = value.length();
            }
            std::string dimensionStr = value.substr(start, end - start);
            dimensions.push_back(std::stoi(dimensionStr));
            start = end + 1;
            SkipWhitespace(value, start);
        }
        if (start >= value.length() || value[start] != ']') {
            throw std::runtime_error("Expected ']'");
        }
        return dimensions;
    }

    Shape* BuildShape(MorphicShape tempShape) {
        Shape* shape = nullptr;
        switch (tempShape.shapeId) {
            case 1: // Line
        }
    }

    // QObject* BuildQObject(int object, const MorphicShape &tempShape) {
    //     switch (object) {
    //         case QPen:
    //             break;
    //         case QBrush:
    //             break;
    //         case QPoint:
    //             break;
    //         case QString:
    //             break;
    //         case QFont:
    //             break;
    //         default:
    //             throw std::runtime_error("Unknown object type");
    //     }

    // }

};

#endif //CONVERTER_H