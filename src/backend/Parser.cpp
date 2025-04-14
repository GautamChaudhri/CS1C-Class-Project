#include "Parser.h"
#include <stdexcept>

// Public functions
void Parser::PrintShapeVector(const alpha::vector<Shape*> &shapes) {
    for (const auto& shape : shapes) {
        std::cout << "Shape ID: " << shape->getShapeId() 
                  << ", Shape Type: " << shape->getShapeType() << std::endl;
    }
}

alpha::vector<Shape*> Parser::JsonToShapes(const std::string& json) {
    alpha::vector<Shape*> shapes;
    Shape* newShape = nullptr;

    size_t index = 0;   // index at '['
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
        if (newShape != nullptr)
            shapes.push_back(newShape);
        else
            std::cout << "Failed to build shape with id: " << tempShape.shapeId << std::endl;

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

// Private functions
Parser::MorphicShape Parser::ParseJsonObject(const std::string json, size_t &index) {
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
        SkipWhitespace(json, index);    // index at value

        std::string value = ExtractValue(json, index);
        SkipWhitespace(json, index);

        UpdateMorphicShape(key, value, tempShape);

        if (json[index] == ',') {       // if comma, loop again
            index++;
            SkipWhitespace(json, index);
        }
        else if (json[index] == '}') {  // if '}', then end of object and break
            index++;
            break;
        }
        else                            // otherwise invalid json string
            throw std::runtime_error("Expected '}' or ','.");
    }
    return tempShape;
}

std::string Parser::ExtractKey(const std::string& json, size_t &index) {
    // index at opening "
    size_t closingQuoteIndex = json.find('"', index + 1);
    size_t keyLength = closingQuoteIndex - index - 1;
    std::string key = json.substr(index + 1, keyLength);
    index = closingQuoteIndex + 1;
    return key;
}

std::string Parser::ExtractValue(const std::string& json, size_t &index) {
    std::string value;

    if (json[index] == '"')             // value is a string
        value = ExtractKey(json, index);
    else if (isdigit(json[index]))      // value is a number
        value = ExtractInteger(json, index);
    else if (json[index] == '[')        // value is an array
        value = ExtractArray(json, index);
    else if (json[index] == 'n')        // value is null
        value = ExtractNull(json, index);
    else
        throw std::runtime_error("Expected '\"', '[', integer, or null.");
    
    return value;
}

std::string Parser::ExtractInteger(const std::string& json, size_t &index) {
    size_t startIndex = index;
    while (isdigit(json[index]))
        index++;
    std::string integerStr = json.substr(startIndex, index - startIndex);
    return integerStr;
}

std::string Parser::ExtractArray(const std::string& json, size_t &index) {
    size_t closingBracketIndex = json.find(']', index + 1);
    if (closingBracketIndex == std::string::npos) {
        throw std::runtime_error("Missing ']' in array");
    }
    std::string arrayStr = json.substr(index, closingBracketIndex + 1);
    index = closingBracketIndex + 1;
    return arrayStr;
}

std::string Parser::ExtractNull(const std::string& json, size_t &index) {
    std::string nullStr = json.substr(index, 4);
    index += 4;
    if (nullStr != "null")
        throw std::runtime_error("Expected null");
    return nullStr;
}

void Parser::SkipWhitespace(const std::string& json, size_t& index) {
    while (index < json.length() && isspace(json[index]))
        ++index;
}

void Parser::UpdateMorphicShape(const std::string &key, const std::string &value, MorphicShape &tempShape) {
    if (key == "ShapeId") {
        tempShape.shapeId = std::stoi(value);
    }
    else if (key == "TrackerId") {
        if (value != "null")
            tempShape.trackerId = std::stoi(value);
        else
            tempShape.trackerId = -1;
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
            tempShape.brush.setColor(Qt::blue);
        else if (value == "white")
            tempShape.brush.setColor(Qt::white);
        else if (value == "lightGray")
            tempShape.brush.setColor(Qt::lightGray);
        else if (value == "darkGray")
            tempShape.brush.setColor(Qt::darkGray);
        else if (value == "black")
            tempShape.brush.setColor(Qt::black);
        else if (value == "transparent")
            tempShape.brush.setColor(Qt::transparent);
        else
            throw std::runtime_error("Unknown pen color: " + value);
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
            tempShape.brush.setColor(Qt::blue);
        else if (value == "white")
            tempShape.brush.setColor(Qt::white);
        else if (value == "lightGray")
            tempShape.brush.setColor(Qt::lightGray);
        else if (value == "darkGray")
            tempShape.brush.setColor(Qt::darkGray);
        else if (value == "black")
            tempShape.brush.setColor(Qt::black);
        else if (value == "transparent")
            tempShape.brush.setColor(Qt::transparent);
        else
            throw std::runtime_error("Unknown brush color: " + value);
    }
    else if (key == "BrushStyle") {
        if (value == "SolidPattern")
            tempShape.brush.setStyle(Qt::SolidPattern);
        else if (value == "VerPattern")
            tempShape.brush.setStyle(Qt::VerPattern);
        else if (value == "HorPattern")
            tempShape.brush.setStyle(Qt::HorPattern);
        else if (value == "Dense1Pattern")
            tempShape.brush.setStyle(Qt::Dense1Pattern);
        else if (value == "CrossPattern")
            tempShape.brush.setStyle(Qt::CrossPattern);
        else if (value == "DiagCrossPattern")
            tempShape.brush.setStyle(Qt::DiagCrossPattern);
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
        if (value == "StyleNormal")
            tempShape.font.setStyle(QFont::StyleNormal);
        else if (value == "StyleItalic")
            tempShape.font.setStyle(QFont::StyleItalic);
        else if (value == "StyleOblique")
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

alpha::vector<int> Parser::StringToVector(const std::string &value) {
    alpha::vector<int> dimensions;
    bool endBracketEncountered = false;
    size_t start = 1;
    SkipWhitespace(value, start);
    while (!endBracketEncountered) {
        size_t end;
        if (value.find(',', start) < value.find(']', start))
            end = value.find(',', start);
        else if (value.find(']', start) < value.find(',', start)) {
            end = value.find(']', start);
            endBracketEncountered = true;
        }
        else
            throw std::runtime_error("Expected ',' or ']'");
        
        std::string dimensionStr = value.substr(start, end - start);
        dimensions.push_back(std::stoi(dimensionStr));
        start = end + 1;
        SkipWhitespace(value, start);
    }
    return dimensions;
}

Shape* Parser::BuildShape(MorphicShape tempShape) {
    Shape* shape;
    switch (tempShape.shapeId) {
        case 1: { // Line
            QPoint startPoint(tempShape.shapeDimensions[0], tempShape.shapeDimensions[1]);
            QPoint endPoint(tempShape.shapeDimensions[2], tempShape.shapeDimensions[3]);
            tempShape.coords = startPoint;
            shape = new Line(tempShape.shapeId, tempShape.shapeType, tempShape.coords, tempShape.pen, tempShape.brush, startPoint, endPoint);
            break;
        }
        case 2: { // Polyline   | REFINE DOUBLE LOOPS LATER
            QPoint* points = new QPoint[tempShape.shapeDimensions.size() / 2];
            int pointsIndex = 0;
            for (int i = 0; i < tempShape.shapeDimensions.size(); i += 2) {
                points[pointsIndex].setX(tempShape.shapeDimensions[i]);
                points[pointsIndex].setY(tempShape.shapeDimensions[i + 1]);
                pointsIndex++;
            }
            tempShape.coords = points[0];
            QPolygon polyList;
            for (int i = 0; i < pointsIndex; ++i)
                polyList << points[i];
            shape = new Polyline(tempShape.shapeId, tempShape.shapeType, tempShape.coords, tempShape.pen, tempShape.brush, polyList);
            break;
        }
        case 3: { // Polygon   | REFINE DOUBLE LOOPS LATER
            QPoint* points = new QPoint[tempShape.shapeDimensions.size() / 2];
            int pointsIndex = 0;
            for (int i = 0; i < tempShape.shapeDimensions.size(); i += 2) {
                points[pointsIndex].setX(tempShape.shapeDimensions[i]);
                points[pointsIndex].setY(tempShape.shapeDimensions[i + 1]);
                pointsIndex++;
            }
            tempShape.coords = points[0];
            QPolygon polyList;
            for (int i = 0; i < pointsIndex; ++i)
                polyList << points[i];
            shape = new Polygon(tempShape.shapeId, tempShape.shapeType, tempShape.coords, tempShape.pen, tempShape.brush, polyList);
            break;
        }
        case 4: { // Rectangle
            tempShape.coords = QPoint(tempShape.shapeDimensions[0], tempShape.shapeDimensions[1]);
            int length = tempShape.shapeDimensions[2];
            int width = tempShape.shapeDimensions[3];
            shape = new Rectangle(tempShape.shapeId, tempShape.shapeType, tempShape.coords, tempShape.pen, tempShape.brush, length, width);
            break;
        }
        case 5: { // Square
            tempShape.coords = QPoint(tempShape.shapeDimensions[0], tempShape.shapeDimensions[1]);
            int length = tempShape.shapeDimensions[2];
            shape = new Square(tempShape.shapeId, tempShape.shapeType, tempShape.coords, tempShape.pen, tempShape.brush, length);
            break;
        }
        case 6: { // Ellipse
            tempShape.coords = QPoint(tempShape.shapeDimensions[0], tempShape.shapeDimensions[1]);
            int a = tempShape.shapeDimensions[2];
            int b = tempShape.shapeDimensions[3];
            shape = new Ellipse(tempShape.shapeId, tempShape.shapeType, tempShape.coords, tempShape.pen, tempShape.brush, a, b);
            break;
        }
        case 7: { // Circle
            tempShape.coords = QPoint(tempShape.shapeDimensions[0], tempShape.shapeDimensions[1]);
            int r = tempShape.shapeDimensions[2];
            shape = new Circle(tempShape.shapeId, tempShape.shapeType, tempShape.coords, tempShape.pen, tempShape.brush, r);
            break;
        }
        case 8: { // Text
            tempShape.coords = QPoint(tempShape.shapeDimensions[0], tempShape.shapeDimensions[1]);
            int length = tempShape.shapeDimensions[2];
            int width = tempShape.shapeDimensions[3];
            shape = new Text(tempShape.shapeId, tempShape.shapeType, tempShape.coords, tempShape.textString, tempShape.textColor, tempShape.textAlignment, tempShape.font, length, width);
            break;
        }
        default: {
            shape = nullptr;
        }
    }
    return shape;
}