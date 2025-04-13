//Converter.h
#ifndef CONVERTER_H
#define CONVERTER_H
#include <iostream>
#include <cctype>
#include "shapes/all_shapes.h"
#include "vector.h"

struct MorphicShape {
    int shapeId = -1;
    int trackerId = -1;
    std::string shapeType = "";
    QPen pen = QPen();
    QBrush brush = QBrush();
    QPoint coords = QPoint();
    QPoint startPoint = QPoint();
    QPoint endPoint = QPoint();
    QPoint* points = nullptr;
    int length = 0;
    int width = 0;
    int r = 0;
    int pointCount = 0;
    int a = 0;
    int b = 0;

    QString textString = "";
    Qt::GlobalColor textColor = Qt::black;
    Qt::AlignmentFlag textAlignment = Qt::AlignLeft;
    QFont font = QFont();
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
        else if (json[index] == 'n')
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
            //
        }
        else if (key == "TrackerId") {
            //
        }
        else if (key == "ShapeType") {
            //
        }
        else if (key == "ShapeDimensions") {
            //
        }
        else if (key == "PenColor") {
            //
        }
        else if (key == "PenWidth") {
            //
        }
        else if (key == "PenStyle") {
            //
        }
        else if (key == "PenCapStyle") {
            //
        }
        else if (key == "PenJoinStyle") {
            //
        }
        else if (key == "BrushColor") {
            //
        }
        else if (key == "BrushStyle") {
            //
        }
        else if (key == "TextString") {
            //
        }
        else if (key == "TextColor") {
            //
        }
        else if (key == "TextAlignment") {
            //
        }
        else if (key == "TextPointSize") {
            //
        }
        else if (key == "TextFontFamily") {
            //
        }
        else if (key == "TextFontStyle") {
            //
        }
        else if (key == "TextFontWeight") {
            //
        }
        else
            throw std::runtime_error("Unknown key: " + key);
    }

    Shape* BuildShape(MorphicShape tempShape) {
        Shape* shape = nullptr;
    }

    

};

#endif //CONVERTER_H