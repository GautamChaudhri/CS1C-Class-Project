#include "Parser.h"
#include <string>

// Public functions
void Parser::PrintShapeVector(const alpha::vector<Shape*> &shapes) {
    for (const auto& shape : shapes) {
        std::cout << "Shape ID: " << shape->getShapeId() 
                  << ", TrackerId: " << shape->getTrackerId()
                  << ", Shape Type: " << shape->getShapeType() << std::endl;
    }
}



alpha::vector<Shape*> Parser::JsonToShapes(const std::string& json) {   //Forward Parser (JSON string -> vector<Shape*>)
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



std::string Parser::ShapesToJson(const alpha::vector<Shape*>& shapes) {     //Reverse Parser (vector<Shape*> -> JSON string)
    std::string json = "[\n";
    for (size_t i = 0; i < shapes.size(); ++i) {
        const Shape* currShape = shapes[i];
        int currShapeId = currShape->getShapeId();
        json += "{\n";
        
        //Add correct data based on shape type
        if (currShapeId < POLYGON)
            json += AppendCommonShapeData(currShape);
        else if (currShapeId >= POLYGON && currShapeId != TEXT) {
            json += AppendCommonShapeData(currShape)+ ",\n" + AppendBrushData(currShape);
        }
        else if (currShapeId == TEXT)
            json += AppendTextData(currShape);

        if (i == shapes.size() - 1) //don't add comma if this is the last object
            json += "\n}\n]\n";
        else
            json += "\n},\n";
    }
    return json;
}



alpha::vector<UserAccount*> Parser::JsonToUsers(const std::string& json) { // Forward Parser for user accounts
    alpha::vector<UserAccount*> out;
    size_t index = 0;
    SkipWhitespace(json, index);
    if (index >= json.size() || json[index] != '[')
        throw std::runtime_error("Expected '[' at start of JSON array");
    ++index;

    while (true) {
        SkipWhitespace(json, index);
        if (index < json.size() && json[index] == ']') { ++index; break; }

        if (index >= json.size() || json[index] != '{')
            throw std::runtime_error("Expected '{' at start of user object");
        ++index;

        RawUser acc;
        // parse one object
        while (true) {
            SkipWhitespace(json, index);
            if (index < json.size() && json[index] == '}') { ++index; break; }
            if (index >= json.size() || json[index] != '\"')
                throw std::runtime_error("Expected '\"' at key");

            std::string key = ExtractKey(json, index);
            SkipWhitespace(json, index);
            if (index >= json.size() || json[index] != ':')
                throw std::runtime_error("Expected ':' after key");
            ++index;
            SkipWhitespace(json, index);

            std::string value = ExtractValue(json, index);
            UpdateUserAccumulator(key, value, acc);
            SkipWhitespace(json, index);

            if (index < json.size() && json[index] == ',') { ++index; continue; }
            else if (index < json.size() && json[index] == '}') continue;
            else throw std::runtime_error("Expected ',' or '}' in object");
        }

        if (!acc.hasUsername || !acc.hasPassword || !acc.hasAdmin)
            throw std::runtime_error("Missing required fields in user object");

        out.push_back(new UserAccount(acc.username, acc.password, acc.admin));
        SkipWhitespace(json, index);

        if (index < json.size() && json[index] == ',') { ++index; continue; }
        else if (index < json.size() && json[index] == ']') { ++index; break; }
        else throw std::runtime_error("Expected ',' or ']' after object");
    }

    return out;
}



std::string Parser::UsersToJson(const alpha::vector<UserAccount*>& users) {    // Reverse Parser for user accounts
    std::string json = "[\n";
    for (size_t index = 0; index < users.size(); ++index) {
        const UserAccount* user = users[index];
        json += "  {\n";
        json += "    \"username\": \"" + user->getUsername().toStdString() + "\",\n";
        json += "    \"password\": \"" + user->getPassword().toStdString() + "\",\n";
        json += "    \"admin\": " + std::string(user->isAdmin() ? "true" : "false") + "\n";
        json += "  }";
        if (index + 1 < users.size()) json += ",";
        json += "\n";
    }
    json += "]";
    return json;
}



QVector<Testimonial> Parser::JsonToTestimonials(const std::string& json) {
    QByteArray data = QByteArray::fromStdString(json);
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError) {
        throw std::runtime_error("Failed to parse testimonials JSON: " +
                                 err.errorString().toStdString());
    }
    if (!doc.isArray()) {
        throw std::runtime_error("Expected JSON array for testimonials");
    }
    QVector<Testimonial> testimonials;
    QJsonArray array = doc.array();
    testimonials.reserve(array.size());
    for (const QJsonValue& v : array) {
        if (!v.isObject()) continue;
        testimonials.append(Testimonial::fromJson(v.toObject()));
    }
    return testimonials;
}



std::string Parser::TestimonialsToJson(const QVector<Testimonial>& testimonials) {
    QJsonArray array;
    for (const Testimonial& t : testimonials) {
        array.append(t.toJson());
    }
    QJsonDocument doc(array);
    QByteArray bytes = doc.toJson(QJsonDocument::Indented);
    return bytes.toStdString();
}

/*==================================== Forward Parser Subroutines ============================================*/

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

        UpdateAccumulator(key, value, tempShape);

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



void Parser::UpdateAccumulator(const std::string &key, const std::string &value, MorphicShape &tempShape) {
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
        tempShape.shapeDimensions = StringToVector(value);
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
            tempShape.pen.setColor(Qt::blue);
        else if (value == "white")
            tempShape.pen.setColor(Qt::white);
        else if (value == "lightGray")
            tempShape.pen.setColor(Qt::lightGray);
        else if (value == "darkGray")
            tempShape.pen.setColor(Qt::darkGray);
        else if (value == "black")
            tempShape.pen.setColor(Qt::black);
        else if (value == "transparent")
            tempShape.pen.setColor(Qt::transparent);
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
            tempShape.textColor = Qt::blue;
        else if (value == "white")
            tempShape.textColor = Qt::white;
        else if (value == "lightGray")
            tempShape.textColor = Qt::lightGray;
        else if (value == "darkGray")
            tempShape.textColor = Qt::darkGray;
        else if (value == "black")
            tempShape.textColor = Qt::black;
        else if (value == "transparent")
            tempShape.textColor = Qt::transparent;
        else
            throw std::runtime_error("Unknown text color: " + value);
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



Shape* Parser::BuildShape(MorphicShape tempShape) {
    Shape* shape;
    switch (tempShape.shapeId) {
        case LINE: {
            QPoint startPoint(tempShape.shapeDimensions[0], tempShape.shapeDimensions[1]);
            QPoint endPoint(tempShape.shapeDimensions[2], tempShape.shapeDimensions[3]);
            tempShape.coords = startPoint;
            shape = new Line(tempShape.shapeType, tempShape.coords, tempShape.pen, tempShape.brush, startPoint, endPoint);
            shape->setShapeId(tempShape.shapeId);
            shape->setTrackerId(tempShape.trackerId);
            break;
        }
        case POLYLINE: {
            QPolygon pointsList;
            QPoint tempPoint;
            for (int i = 0; i < tempShape.shapeDimensions.size(); i += 2) {
                tempPoint.setX(tempShape.shapeDimensions[i]);
                tempPoint.setY(tempShape.shapeDimensions[i + 1]);
                pointsList << tempPoint;
            }
            tempShape.coords = pointsList[0];
            shape = new Polyline(tempShape.shapeType, tempShape.coords, tempShape.pen, tempShape.brush, pointsList);
            shape->setShapeId(tempShape.shapeId);
            shape->setTrackerId(tempShape.trackerId);
            break;
        }
        case POLYGON: {
            QPolygon pointsList;
            QPoint tempPoint;
            for (int i = 0; i < tempShape.shapeDimensions.size(); i += 2) {
                tempPoint.setX(tempShape.shapeDimensions[i]);
                tempPoint.setY(tempShape.shapeDimensions[i + 1]);
                pointsList << tempPoint;
            }
            tempShape.coords = pointsList[0];
            shape = new Polygon(tempShape.shapeType, tempShape.coords, tempShape.pen, tempShape.brush, pointsList);
            shape->setShapeId(tempShape.shapeId);
            shape->setTrackerId(tempShape.trackerId);
            break;
        }
        case RECTANGLE: {
            tempShape.coords = QPoint(tempShape.shapeDimensions[0], tempShape.shapeDimensions[1]);
            int length = tempShape.shapeDimensions[2];
            int width = tempShape.shapeDimensions[3];
            shape = new Rectangle(tempShape.shapeType, tempShape.coords, tempShape.pen, tempShape.brush, length, width);
            shape->setShapeId(tempShape.shapeId);
            shape->setTrackerId(tempShape.trackerId);
            break;
        }
        case SQUARE: {
            tempShape.coords = QPoint(tempShape.shapeDimensions[0], tempShape.shapeDimensions[1]);
            int length = tempShape.shapeDimensions[2];
            shape = new Square(tempShape.shapeType, tempShape.coords, tempShape.pen, tempShape.brush, length);
            shape->setShapeId(tempShape.shapeId);
            shape->setTrackerId(tempShape.trackerId);
            break;
        }
        case ELLIPSE: {
            tempShape.coords = QPoint(tempShape.shapeDimensions[0], tempShape.shapeDimensions[1]);
            int a = tempShape.shapeDimensions[2];
            int b = tempShape.shapeDimensions[3];
            shape = new Ellipse(tempShape.shapeType, tempShape.coords, tempShape.pen, tempShape.brush, a, b);
            shape->setShapeId(tempShape.shapeId);
            shape->setTrackerId(tempShape.trackerId);
            break;
        }
        case CIRCLE: {
            tempShape.coords = QPoint(tempShape.shapeDimensions[0], tempShape.shapeDimensions[1]);
            int r = tempShape.shapeDimensions[2];
            shape = new Circle(tempShape.shapeType, tempShape.coords, tempShape.pen, tempShape.brush, r);
            shape->setShapeId(tempShape.shapeId);
            shape->setTrackerId(tempShape.trackerId);
            break;
        }
        case TEXT: {
            tempShape.coords = QPoint(tempShape.shapeDimensions[0], tempShape.shapeDimensions[1]);
            int length = tempShape.shapeDimensions[2];
            int width = tempShape.shapeDimensions[3];
            shape = new Text(tempShape.shapeType, tempShape.coords, tempShape.textString, tempShape.textColor, tempShape.textAlignment, tempShape.font, length, width);
            shape->setShapeId(tempShape.shapeId);
            shape->setTrackerId(tempShape.trackerId);
            break;
        }
        default: {
            shape = nullptr;
        }
    }
    return shape;
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

    if (json[index] == '"')             // value is a string so same extraction process as key
        value = ExtractKey(json, index);
    else if (isdigit(json[index]))      // value is a number
        value = ExtractInteger(json, index);
    else if (json[index] == '[')        // value is an array
        value = ExtractArray(json, index);
    else if (json[index] == 't' || json[index] == 'f')  // value is a boolean
        value = ExtractLiteral(json, index);
    else
        throw std::runtime_error("Expected '\"', '[', or integer.");
    
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

void Parser::SkipWhitespace(const std::string& json, size_t& index) {
    while (index < json.length() && isspace(json[index]))
        ++index;
}

std::string Parser::ExtractLiteral(const std::string& json, size_t& index) {
    size_t start = index;
    while (index < json.size() && std::isalpha(static_cast<unsigned char>(json[index])))
        ++index;
    return json.substr(start, index - start);
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

/*==================================== Reverse Parser Subroutines ============================================*/

std::string Parser::AppendCommonShapeData(const Shape* shape) {
    std::string commonData;
        commonData += "\"ShapeId\": " + std::to_string(shape->getShapeId()) + ",\n"
                   += "\"TrackerId\": " + std::to_string(shape->getTrackerId()) + ",\n"
                   += "\"ShapeType\": \"" + shape->getShapeType() + "\",\n"
                   += "\"ShapeDimensions\": " + GetShapeDimensions(shape) + ",\n"
                   += "\"PenColor\": \"" + GetColor(shape->getPenColor()) + "\",\n"
                   += "\"PenWidth\": " + std::to_string(shape->getPen().width()) + ",\n"
                   += "\"PenStyle\": \"" + GetPenStyle(shape) + "\",\n"
                   += "\"PenCapStyle\": \"" + GetPenCapStyle(shape) + "\",\n"
                   += "\"PenJoinStyle\": \"" + GetPenJoinStyle(shape) + "\"";
    return commonData;
}



std::string Parser::AppendBrushData(const Shape* shape) {
    std::string brushData;
    brushData += "\"BrushColor\": \"" + GetColor(shape->getBrushColor()) + "\",\n"
              += "\"BrushStyle\": \"" + GetBrushStyle(shape) + "\"";
    return brushData;
}



std::string Parser::AppendTextData(const Shape* shape) {
    const Text* text = static_cast<const Text*>(shape);
    if (!text) throw std::runtime_error("Dynamic Cast to Text pointer failed.");
    std::string textData;
    textData += "\"ShapeId\": " + std::to_string(shape->getShapeId()) + ",\n"
             += "\"TrackerId\": " + std::to_string(shape->getTrackerId()) + ",\n"
             += "\"ShapeType\": \"" + shape->getShapeType() + "\",\n"
             += "\"ShapeDimensions\": " + GetShapeDimensions(shape) + ",\n"
             += "\"TextString\": \"" + text->getTextString().toStdString() + "\",\n"
             += "\"TextPointSize\": " + std::to_string(text->getFont().pointSize()) + ",\n"
             += "\"TextColor\": \"" + GetColor(text->getTextColor()) + "\",\n"
             += "\"TextAlignment\": \"" + GetAlignmentFlag(text) + "\",\n"
             += "\"TextFontFamily\": \"" + text->getFont().family().toStdString() + "\",\n"
             += "\"TextFontStyle\": \"" + GetFontStyle(text) + "\",\n"
             += "\"TextFontWeight\": \"" + GetFontWeight(text) + "\"";
    return textData;
}



std::string Parser::GetShapeDimensions(const Shape* shape) {
    std::string dimensions = "[";
    switch (shape->getShapeId()) {
        case 1: {   //Line
            //Line pointer needed to access following get functions since they are 
            //only defined in the derived classes. Same follows for all cases.
            const Line* line = static_cast<const Line*>(shape);
            if (!line) throw std::runtime_error("Dynamic Cast to Line pointer failed.");
            //Get the necessary points
            std::string startX = std::to_string(line->getStartPoint().x());
            std::string startY = std::to_string(line->getStartPoint().y());
            std::string endX = std::to_string(line->getEndPoint().x());
            std::string endY = std::to_string(line->getEndPoint().y());
            dimensions += startX + ", " + startY + ", " + endX + ", " + endY + "]";
            break;
        }
        case 2: {   // Polyline
            const Polyline* polyline = static_cast<const Polyline*>(shape);
            if (!polyline)
                throw std::runtime_error("Dynamic Cast to Polyline pointer failed.");
            QPolygon points = polyline->getPointsList();
            // Loop over each point and add its x and y values
            for (int i = 0; i < points.size(); ++i) {
                std::string x = std::to_string(points.at(i).x());
                std::string y = std::to_string(points.at(i).y());
                dimensions += x + ", " + y;
                if (i < points.size() - 1)
                    dimensions += ", ";
            }
            dimensions += "]";
            break;
        }
        case 3: {   // Polygon
            const Polygon* polygon = static_cast<const Polygon*>(shape);
            if (!polygon)
                throw std::runtime_error("Dynamic Cast to Polygon pointer failed.");
            QPolygon points = polygon->getPointsList();
            // Loop over each point and add its x and y values
            for (int i = 0; i < points.size(); ++i) {
                std::string x = std::to_string(points.at(i).x());
                std::string y = std::to_string(points.at(i).y());
                dimensions += x + ", " + y;
                if (i < points.size() - 1)
                    dimensions += ", ";
            }
            dimensions += "]";
            break;
        }
        case 4: { // Rectangle
            const Rectangle* rect = static_cast<const Rectangle*>(shape);
            if (!rect)
                throw std::runtime_error("Dynamic Cast to Rectangle pointer failed.");
            QPoint coordinates = shape->getPoints();
            std::string x = std::to_string(coordinates.x());
            std::string y = std::to_string(coordinates.y());
            std::string length = std::to_string(rect->getLength());
            std::string width = std::to_string(rect->getWidth());
            dimensions += x + ", " + y + ", " + length + ", " + width + "]";
            break;
        }
        case 5: { // Square
            const Square* square = static_cast<const Square*>(shape);
            if (!square)
                throw std::runtime_error("Dynamic Cast to Square pointer failed.");
            // Get the coordinate from the base Shape's getPoints() method.
            QPoint coordinates = shape->getPoints();
            std::string x = std::to_string(coordinates.x());
            std::string y = std::to_string(coordinates.y());
            std::string length = std::to_string(square->getLength());
            dimensions += x + ", " + y + ", " + length + "]";
            break;
        }
        case 6: { // Ellipse
            const Ellipse* ellipse = static_cast<const Ellipse*>(shape);
            if (!ellipse)
                throw std::runtime_error("Dynamic Cast to Ellipse pointer failed.");
            // Get the coordinate from the base Shape's getPoints() method.
            QPoint coordinates = shape->getPoints();
            std::string x = std::to_string(coordinates.x());
            std::string y = std::to_string(coordinates.y());
            std::string aVal = std::to_string(ellipse->getA());
            std::string bVal = std::to_string(ellipse->getB());
            dimensions += x + ", " + y + ", " + aVal + ", " + bVal + "]";
            break;
        }
        case 7: { // Circle
            const Circle* circle = static_cast<const Circle*>(shape);
            if (!circle)
                throw std::runtime_error("Dynamic Cast to Circle pointer failed.");
            QPoint coordinates = shape->getPoints();
            std::string x = std::to_string(coordinates.x());
            std::string y = std::to_string(coordinates.y());
            std::string radius = std::to_string(circle->getR());
            dimensions += x + ", " + y + ", " + radius + "]";
            break;
        }
        case 8: { // Text
            const Text* text = static_cast<const Text*>(shape);
            if (!text)
                throw std::runtime_error("Dynamic Cast to Text pointer failed.");
            QPoint coordinates = shape->getPoints();
            std::string x = std::to_string(coordinates.x());
            std::string y = std::to_string(coordinates.y());
            std::string length = std::to_string(text->getLength());
            std::string width = std::to_string(text->getWidth());
            dimensions += x + ", " + y + ", " + length + ", " + width + "]";
            break;
        }
        default:
            throw std::runtime_error("Unknown ShapeId: " + std::to_string(shape->getShapeId()));
    }
    return dimensions;
}



std::string Parser::GetColor(const QColor &objectColor) {
    std::string colorStr;
    if (objectColor == Qt::red)
        colorStr = "red";
    else if (objectColor == Qt::green)
        colorStr = "green";
    else if (objectColor == Qt::yellow)
        colorStr = "yellow";
    else if (objectColor == Qt::cyan)
        colorStr = "cyan";
    else if (objectColor == Qt::magenta)
        colorStr = "magenta";
    else if (objectColor == Qt::gray)
        colorStr = "gray";
    else if (objectColor == Qt::blue)
        colorStr = "blue";
    else if (objectColor == Qt::white)
        colorStr = "white";
    else if (objectColor == Qt::lightGray)
        colorStr = "lightGray";
    else if (objectColor == Qt::darkGray)
        colorStr = "darkGray";
    else if (objectColor == Qt::black)
        colorStr = "black";
    else if (objectColor == Qt::transparent)
        colorStr = "transparent";
    else
        throw std::runtime_error("Encountered unknown pen color.");
    return colorStr;
}



std::string Parser::GetPenStyle(const Shape* shape) {
    std::string style;
    PenStyle penStyle = shape->getPenStyle();
    if (penStyle == Qt::SolidLine)
        style = "SolidLine";
    else if (penStyle == Qt::DashLine)
        style = "DashLine";
    else if (penStyle == Qt::DotLine)
        style = "DotLine";
    else if (penStyle == Qt::DashDotLine)
        style = "DashDotLine";
    else if (penStyle == Qt::DashDotDotLine)
        style = "DashDotDotLine";
    else
        throw std::runtime_error("Unknown pen style at ShapeId: " + shape->getShapeId());
    return style;
}



std::string Parser::GetPenCapStyle(const Shape* shape) {
    std::string capStyle;
    PenCapStyle penCapStyle = shape->getPenCapStyle();
    if (penCapStyle == Qt::FlatCap)
        capStyle = "FlatCap";
    else if (penCapStyle == Qt::SquareCap)
        capStyle = "SquareCap";
    else if (penCapStyle == Qt::RoundCap)
        capStyle = "RoundCap";
    else
        throw std::runtime_error("Unknown pen cap style at ShapeId: " + shape->getShapeId());
    return capStyle;
}



std::string Parser::GetPenJoinStyle(const Shape* shape) {
    std::string joinStyle;
    PenJoinStyle penJoinStyle = shape->getPenJoinStyle();
    if (penJoinStyle == Qt::MiterJoin)
        joinStyle = "MiterJoin";
    else if (penJoinStyle == Qt::BevelJoin)
        joinStyle = "BevelJoin";
    else if (penJoinStyle == Qt::RoundJoin)
        joinStyle = "RoundJoin";
    else
        throw std::runtime_error("Unknown pen join style at ShapeId: " + shape->getShapeId());
    return joinStyle;
}



std::string Parser::GetBrushStyle(const Shape* shape) {
    std::string style;
    BrushStyle brushStyle = shape->getBrushStyle();
    if (brushStyle == Qt::SolidPattern)
        style = "SolidPattern";
    else if (brushStyle == Qt::VerPattern)
        style = "VerPattern";
    else if (brushStyle == Qt::HorPattern)
        style = "HorPattern";
    else if (brushStyle == Qt::Dense1Pattern)
        style = "Dense1Pattern";
    else if (brushStyle == Qt::CrossPattern)
        style = "CrossPattern";
    else if (brushStyle == Qt::DiagCrossPattern)
        style = "DiagCrossPattern";
    else if (brushStyle == Qt::NoBrush)
        style = "NoBrush";
    else
        throw std::runtime_error("Unknown brush style at ShapeId: " + shape->getShapeId());
    return style;
}



std::string Parser::GetAlignmentFlag(const Text* text) {
    AlignmentFlag flag = text->getTextAlignment();
    if (flag == Qt::AlignLeft)
        return "AlignLeft";
    else if (flag == Qt::AlignRight)
        return "AlignRight";
    else if (flag == Qt::AlignHCenter)
        return "AlignHCenter";
    else if (flag == Qt::AlignJustify)
        return "AlignJustify";
    else if (flag == Qt::AlignTop)
        return "AlignTop";
    else if (flag == Qt::AlignBottom)
        return "AlignBottom";
    else if (flag == Qt::AlignVCenter)
        return "AlignVCenter";
    else if (flag == Qt::AlignCenter)
        return "AlignCenter";
    else
        throw std::runtime_error("Unknown text alignment flag encountered: " + std::to_string(static_cast<int>(flag)));
}



std::string Parser::GetFontStyle(const Text* text) {
    QFont::Style style = text->getFont().style();
    if (style == QFont::StyleNormal)
        return "StyleNormal";
    else if (style == QFont::StyleItalic)
        return "StyleItalic";
    else if (style == QFont::StyleOblique)
        return "StyleOblique";
    else
        throw std::runtime_error("Unknown font style encountered: " + std::to_string(static_cast<int>(style)));
}



std::string Parser::GetFontWeight(const Text* text) {
    int weight = text->getFont().weight();
    if (weight == QFont::Normal)
        return "Normal";
    else if (weight == QFont::Bold)
        return "Bold";
    else if (weight == QFont::Light)
        return "Light";
    else
        throw std::runtime_error("Unknown font weight encountered: " + std::to_string(weight));
}



void Parser::UpdateUserAccumulator(const std::string& key, const std::string& value, RawUser& acc) {
    if (key == "username") {
        acc.username    = QString::fromStdString(value);
        acc.hasUsername = true;
    }
    else if (key == "password") {
        acc.password    = QString::fromStdString(value);
        acc.hasPassword = true;
    }
    else if (key == "admin") {
        if      (value == "true")  acc.admin = true;
        else if (value == "false") acc.admin = false;
        else throw std::runtime_error("Invalid boolean for admin: " + value);
        acc.hasAdmin = true;
    }
}
