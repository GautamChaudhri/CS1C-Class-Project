#include "RenderAreaManager.h"

RenderAreaManager::RenderAreaManager(QObject* parent) : QObject{parent}, client{}, parse{} {
    connect(&client, &ApiClient::GoodGetReply, this, &RenderAreaManager::onGoodGetResponse);
    connect(&client, &ApiClient::BadGetReply, this, &RenderAreaManager::onBadGetResponse);
    connect(&client, &ApiClient::GoodPostReply, this, &RenderAreaManager::onGoodPostResponse);
    connect(&client, &ApiClient::BadPostReply, this, &RenderAreaManager::onBadPostResponse);
    connect(&client, &ApiClient::GoodDeleteReply, this, &RenderAreaManager::onGoodDeleteResponse);
    connect(&client, &ApiClient::BadDeleteReply, this, &RenderAreaManager::onBadDeleteResponse);
    //loadShapes();
}

RenderAreaManager::~RenderAreaManager() {
    for (size_t i = 0; i < renderedShapes.size(); ++i)
        delete renderedShapes[i];
}

alpha::vector<Shape*>* RenderAreaManager::getShapesRef() {
    return &renderedShapes;
}



void RenderAreaManager::addShape(Shape* shape) {
    qDebug().noquote().nospace() << "[RenderAreaManager::addShape] adding trackerId=" << shape->getTrackerId();
    renderedShapes.push_back(shape);
    emit renderAreaChanged();
    saveShapes();
}

void RenderAreaManager::modifyShape(Shape* shape, QString key, int value) {
    qDebug() << "[modifyShape] called for trackerId=" << shape->getTrackerId()
             << "  key=\"" << key << "\"  value=" << value;

    int shapeId = shape->getShapeId();
    bool shapeModified = false;

    switch (shapeId) {
        case LINE:
        {
            Line* line = static_cast<Line*>(shape);

            if (key == "X:")
            {
                line->Move(value, line->getY());
                shapeModified = true;
            }
            else if (key == "Y:")
            {
                line->Move(line->getX(), value);
                shapeModified = true;
            }
            else if (key == "X1:")
            {
                QPoint startPoint = line->getStartPoint();
                startPoint.setX(value);
                line->setStartPoint(startPoint);
                shapeModified = true;
            }
            else if (key == "Y1:")
            {
                QPoint startPoint = line->getStartPoint();
                startPoint.setY(value);
                line->setStartPoint(startPoint);
                shapeModified = true;
            }
            else if (key == "X2:")
            {
                QPoint endPoint = line->getEndPoint();
                endPoint.setX(value);
                line->setEndPoint(endPoint);
                shapeModified = true;
            }
            else if (key == "Y2:")
            {
                QPoint endPoint = line->getEndPoint();
                endPoint.setY(value);
                line->setEndPoint(endPoint);
                shapeModified = true;
            }
            else if (key == "PenColor:")
            {
                shape->setInternalPen().setColor(static_cast<Qt::GlobalColor>(value));
                shapeModified = true;
            }
            else if (key == "PenWidth:")
            {
                if (value >= 0 && value <= 20)
                {
                    shape->setInternalPen().setWidth(value);
                    shapeModified = true;
                }
                else
                {
                    qDebug() << "[RenderAreaManager::modifyShape] Invalid pen width:" << value;
                }
            }
            else if (key == "PenStyle:")
            {
                shape->setInternalPen().setStyle(static_cast<Qt::PenStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenCapStyle:")
            {
                shape->setInternalPen().setCapStyle(static_cast<Qt::PenCapStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenJoinStyle:")
            {
                shape->setInternalPen().setJoinStyle(static_cast<Qt::PenJoinStyle>(value));
                shapeModified = true;
            }
            else
            {
                 qDebug() << "[RenderAreaManager::modifyShape] Line - key not found:" << key;
            }
            break;
        }
        case POLYLINE:
        {
            Polyline* polyline = static_cast<Polyline*>(shape);

            if (key == "X:")
            {
                polyline->Move(value, polyline->getY());
                shapeModified = true;
            }
            else if (key == "Y:")
            {
                polyline->Move(polyline->getX(), value);
                shapeModified = true;
            }
            else if (key.startsWith("X"))
            {
                QPolygon points = polyline->getPointsList();
                int pointIndex = key.mid(1, key.length() - 2).toInt() - 1;
                if (pointIndex >= 0 && pointIndex < points.size())
                {
                    points[pointIndex].setX(value);
                    polyline->setPointsList(points);
                    shapeModified = true;
                }
            }
            else if (key.startsWith("Y"))
            {
                QPolygon points = polyline->getPointsList();
                int pointIndex = key.mid(1, key.length() - 2).toInt() - 1;
                if (pointIndex >= 0 && pointIndex < points.size())
                {
                    points[pointIndex].setY(value);
                    polyline->setPointsList(points);
                    shapeModified = true;
                }
            }
             else if (key == "PenColor:")
            {
                shape->setInternalPen().setColor(static_cast<Qt::GlobalColor>(value));
                shapeModified = true;
            }
            else if (key == "PenWidth:")
            {
                 if (value >= 0 && value <= 20)
                 {
                    shape->setInternalPen().setWidth(value);
                    shapeModified = true;
                 }
                 else
                 {
                    qDebug() << "[RenderAreaManager::modifyShape] Invalid pen width:" << value;
                 }
            }
            else if (key == "PenStyle:")
            {
                shape->setInternalPen().setStyle(static_cast<Qt::PenStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenCapStyle:")
            {
                shape->setInternalPen().setCapStyle(static_cast<Qt::PenCapStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenJoinStyle:")
            {
                shape->setInternalPen().setJoinStyle(static_cast<Qt::PenJoinStyle>(value));
                shapeModified = true;
            }
            else
            {
                 qDebug() << "[RenderAreaManager::modifyShape] Polyline - key not found:" << key;
            }
            break;
        }
        case POLYGON:
        {
            Polygon* polygon = static_cast<Polygon*>(shape);

            if (key == "X:")
            {
                polygon->Move(value, polygon->getY());
                shapeModified = true;
            }
            else if (key == "Y:")
            {
                polygon->Move(polygon->getX(), value);
                shapeModified = true;
            }
            else if (key.startsWith("X"))
            {
                QPolygon points = polygon->getPointsList();
                int pointIndex = key.mid(1, key.length() - 2).toInt() - 1;
                if (pointIndex >= 0 && pointIndex < points.size())
                {
                    points[pointIndex].setX(value);
                    polygon->setPointsList(points);
                    shapeModified = true;
                }
            }
            else if (key.startsWith("Y"))
            {
                QPolygon points = polygon->getPointsList();
                int pointIndex = key.mid(1, key.length() - 2).toInt() - 1;
                if (pointIndex >= 0 && pointIndex < points.size())
                {
                    points[pointIndex].setY(value);
                    polygon->setPointsList(points);
                    shapeModified = true;
                }
            }
            else if (key == "Pen:")
            {
                shape->setInternalPen().setStyle(static_cast<Qt::PenStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenColor:")
            {
                shape->setInternalPen().setColor(static_cast<Qt::GlobalColor>(value));
                shapeModified = true;
            }
            else if (key == "PenWidth:")
            {
                if (value >= 0 && value <= 20)
                {
                    shape->setInternalPen().setWidth(value);
                    shapeModified = true;
                }
                else
                {
                    qDebug() << "[RenderAreaManager::modifyShape] Invalid pen width:" << value;
                }
            }
            else if (key == "PenStyle:")
            {
                shape->setInternalPen().setStyle(static_cast<Qt::PenStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenCapStyle:")
            {
                shape->setInternalPen().setCapStyle(static_cast<Qt::PenCapStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenJoinStyle:")
            {
                shape->setInternalPen().setJoinStyle(static_cast<Qt::PenJoinStyle>(value));
                shapeModified = true;
            }
            else if (key == "Brush:")
            {
                shape->setInternalBrush().setStyle(static_cast<Qt::BrushStyle>(value));
                shapeModified = true;
            }
            else if (key == "BrushColor:")
            {
                shape->setInternalBrush().setColor(static_cast<Qt::GlobalColor>(value));
                shapeModified = true;
            }
            else
            {
                 qDebug() << "[RenderAreaManager::modifyShape] Polygon - key not found:" << key;
            }
            break;
        }
        case RECTANGLE:
        {
            Rectangle* pRectangle = static_cast<Rectangle*>(shape);
            if (key == "X:") {
                pRectangle->setX(value);
                shapeModified = true;
            }
            else if (key == "Y:") {
                pRectangle->setY(value);
                shapeModified = true;
            }
            else if (key == "Length:") {
                pRectangle->setLength(value);
                shapeModified = true;
            }
            else if (key == "Width:") {
                pRectangle->setWidth(value);
                shapeModified = true;
            }
            else if (key == "Pen:")
            {
                shape->setInternalPen().setStyle(static_cast<Qt::PenStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenColor:")
            {
                shape->setInternalPen().setColor(static_cast<Qt::GlobalColor>(value));
                shapeModified = true;
            }
            else if (key == "PenWidth:")
            {
                if (value >= 0 && value <= 20)
                {
                    shape->setInternalPen().setWidth(value);
                    shapeModified = true;
                }
                else
                {
                    qDebug() << "[RenderAreaManager::modifyShape] Invalid pen width:" << value;
                }
            }
            else if (key == "PenStyle:")
            {
                shape->setInternalPen().setStyle(static_cast<Qt::PenStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenCapStyle:")
            {
                shape->setInternalPen().setCapStyle(static_cast<Qt::PenCapStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenJoinStyle:")
            {
                shape->setInternalPen().setJoinStyle(static_cast<Qt::PenJoinStyle>(value));
                shapeModified = true;
            }
            else if (key == "Brush:")
            {
                shape->setInternalBrush().setStyle(static_cast<Qt::BrushStyle>(value));
                shapeModified = true;
            }
            else if (key == "BrushColor:")
            {
                shape->setInternalBrush().setColor(static_cast<Qt::GlobalColor>(value));
                shapeModified = true;
            }
            else
            {
                 qDebug() << "[RenderAreaManager::modifyShape] Rectangle - key not found:" << key;
            }
            break;
        }
        case SQUARE:
        {
            Square* pSquare = static_cast<Square*>(shape);
            if (key == "X:") {
                pSquare->setX(value);
                shapeModified = true;
            }
            else if (key == "Y:") {
                pSquare->setY(value);
                shapeModified = true;
            }
            else if (key == "Length:") {
                pSquare->setLength(value);
                shapeModified = true;
            }
            else if (key == "Pen:")
            {
                shape->setInternalPen().setStyle(static_cast<Qt::PenStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenColor:")
            {
                shape->setInternalPen().setColor(static_cast<Qt::GlobalColor>(value));
                shapeModified = true;
            }
            else if (key == "PenWidth:")
            {
                if (value >= 0 && value <= 20)
                {
                    shape->setInternalPen().setWidth(value);
                    shapeModified = true;
                }
                else
                {
                    qDebug() << "[RenderAreaManager::modifyShape] Invalid pen width:" << value;
                }
            }
            else if (key == "PenStyle:")
            {
                shape->setInternalPen().setStyle(static_cast<Qt::PenStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenCapStyle:")
            {
                shape->setInternalPen().setCapStyle(static_cast<Qt::PenCapStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenJoinStyle:")
            {
                shape->setInternalPen().setJoinStyle(static_cast<Qt::PenJoinStyle>(value));
                shapeModified = true;
            }
            else if (key == "Brush:")
            {
                shape->setInternalBrush().setStyle(static_cast<Qt::BrushStyle>(value));
                shapeModified = true;
            }
            else if (key == "BrushColor:")
            {
                shape->setInternalBrush().setColor(static_cast<Qt::GlobalColor>(value));
                shapeModified = true;
            }
            else
            {
                 qDebug() << "[RenderAreaManager::modifyShape] Square - key not found:" << key;
            }
            break;
        }
        case ELLIPSE:
        {
            Ellipse* pEllipse = static_cast<Ellipse*>(shape);
            if (key == "X:") {
                pEllipse->setX(value);
                shapeModified = true;
            }
            else if (key == "Y:") {
                pEllipse->setY(value);
                shapeModified = true;
            }
            else if (key == "Semi-Minor Axis:") {
                pEllipse->setA(value);
                shapeModified = true;
            }
            else if (key == "Semi-Major Axis:") {
                pEllipse->setB(value);
                shapeModified = true;
            }
            else if (key == "Pen:")
            {
                shape->setInternalPen().setStyle(static_cast<Qt::PenStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenColor:")
            {
                shape->setInternalPen().setColor(static_cast<Qt::GlobalColor>(value));
                shapeModified = true;
            }
            else if (key == "PenWidth:")
            {
                if (value >= 0 && value <= 20)
                {
                    shape->setInternalPen().setWidth(value);
                    shapeModified = true;
                }
                else
                {
                    qDebug() << "[RenderAreaManager::modifyShape] Invalid pen width:" << value;
                }
            }
            else if (key == "PenStyle:")
            {
                shape->setInternalPen().setStyle(static_cast<Qt::PenStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenCapStyle:")
            {
                shape->setInternalPen().setCapStyle(static_cast<Qt::PenCapStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenJoinStyle:")
            {
                shape->setInternalPen().setJoinStyle(static_cast<Qt::PenJoinStyle>(value));
                shapeModified = true;
            }
            else if (key == "Brush:")
            {
                shape->setInternalBrush().setStyle(static_cast<Qt::BrushStyle>(value));
                shapeModified = true;
            }
            else if (key == "BrushColor:")
            {
                shape->setInternalBrush().setColor(static_cast<Qt::GlobalColor>(value));
                shapeModified = true;
            }
            else
            {
                 qDebug() << "[RenderAreaManager::modifyShape] Ellipse - key not found:" << key;
            }
            break;
        }
        case CIRCLE:
        {
            Circle* pCircle = static_cast<Circle*>(shape);
            if (key == "X:") {
                pCircle->setX(value);
                shapeModified = true;
            }
            else if (key == "Y:") {
                pCircle->setY(value);
                shapeModified = true;
            }
            else if (key == "Radius:") {
                pCircle->setR(value);
                shapeModified = true;
            }
            else if (key == "Pen:")
            {
                shape->setInternalPen().setStyle(static_cast<Qt::PenStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenColor:")
            {
                shape->setInternalPen().setColor(static_cast<Qt::GlobalColor>(value));
                shapeModified = true;
            }
            else if (key == "PenWidth:")
            {
                if (value >= 0 && value <= 20)
                {
                    shape->setInternalPen().setWidth(value);
                    shapeModified = true;
                }
                else
                {
                    qDebug() << "[RenderAreaManager::modifyShape] Invalid pen width:" << value;
                }
            }
            else if (key == "PenStyle:")
            {
                shape->setInternalPen().setStyle(static_cast<Qt::PenStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenCapStyle:")
            {
                shape->setInternalPen().setCapStyle(static_cast<Qt::PenCapStyle>(value));
                shapeModified = true;
            }
            else if (key == "PenJoinStyle:")
            {
                shape->setInternalPen().setJoinStyle(static_cast<Qt::PenJoinStyle>(value));
                shapeModified = true;
            }
            else if (key == "Brush:")
            {
                shape->setInternalBrush().setStyle(static_cast<Qt::BrushStyle>(value));
                shapeModified = true;
            }
            else if (key == "BrushColor:")
            {
                shape->setInternalBrush().setColor(static_cast<Qt::GlobalColor>(value));
                shapeModified = true;
            }
            else
            {
                 qDebug() << "[RenderAreaManager::modifyShape] Circle - key not found:" << key;
            }
            break;
        }
        case TEXT:
        {
            Text* pText = static_cast<Text*>(shape);
            if (key == "X:") {
                pText->setX(value);
                shapeModified = true;
            }
            else if (key == "Y:") {
                pText->setY(value);
                shapeModified = true;
            }
            else if (key == "Length:") {
                pText->setLength(value);
                shapeModified = true;
            }
            else if (key == "Width:") {
                pText->setWidth(value);
                shapeModified = true;
            }
            else if (key == "Alignment:")
            {
                pText->setAlignment(static_cast<Qt::AlignmentFlag>(value));
                shapeModified = true;
            }
            else if (key == "Font:")
            {
                switch (value) {
                    case 0:
                        pText->setInternalFont().setFamily("Arial");
                        shapeModified = true;
                        break;
                    case 1:
                        pText->setInternalFont().setFamily("Times New Roman");
                        shapeModified = true;
                        break;
                    case 2:
                        pText->setInternalFont().setFamily("Courier New");
                        shapeModified = true;
                        break;
                    case 3:
                        pText->setInternalFont().setFamily("Verdana");
                        shapeModified = true;
                        break;
                    case 4:
                        pText->setInternalFont().setFamily("Tahoma");
                        shapeModified = true;
                        break;
                    case 5:
                        pText->setInternalFont().setFamily("Comic Sans MS");
                        shapeModified = true;
                        break;
                    default:
                        qDebug() << "[RenderAreaManager::modifyShape] Unknown font index:" << value;
                }
            }
            else if (key == "FontStyle:")
            {
                pText->setInternalFont().setStyle(static_cast<QFont::Style>(value));
                shapeModified = true;
            }
            else if (key == "FontWeight:")
            {
                pText->setInternalFont().setWeight(static_cast<QFont::Weight>(value));
                shapeModified = true;
            }
            else if (key == "TextColor:")
            {
                pText->setInternalPen().setColor(static_cast<Qt::GlobalColor>(value));
                shapeModified = true;
            }
            else
            {
                 qDebug() << "[RenderAreaManager::modifyShape] Text - key not found:" << key;
            }
            break;
        }
        default:
            qDebug() << "[RenderAreaManager::modifyShape] Unknown shape type. ShapeId: " << shapeId;
            return;
    }

    if (shapeModified) {
        emit renderAreaChanged();
        saveShapes();
    }
}

void RenderAreaManager::modifyDisplayedText(Text* obj, QString newText) {
    obj->setText(newText);
    emit renderAreaChanged();
    saveShapes();
}

void RenderAreaManager::deleteShape(const int trackerId) {
    bool shapeFound = false;

    for (size_t i = 0; i < renderedShapes.size() && !shapeFound; ++i) {
        if (renderedShapes[i]->getTrackerId() == trackerId) {
            delete renderedShapes[i];
            renderedShapes.erase(renderedShapes.begin() + i);
            qDebug().noquote().nospace() << "[RenderAreaManager::deleteShape] deleted trackerId=" << trackerId;
            emit renderAreaChanged();
            saveShapes();
        }
    }

    if (!shapeFound) {
        qDebug().noquote().nospace() << "[RenderAreaManager::deleteShape] not_found trackerId=" << trackerId;
        QString message = "Shape not found. TrackerId: " + QString::number(trackerId);
        emit renderAreaNotChanged(message);
    }
}

void RenderAreaManager::deleteAllShapes() {
    for (Shape* shape : renderedShapes)
        delete shape;
    emit renderAreaChanged();
    //renderedShapes.clear();
    client.DeleteShapesAll();
    qDebug().noquote().nospace() << "[RenderAreaManager::deleteAllShapes] requested_all_delete";
}

void RenderAreaManager::loadShapes() {
    qDebug() << "[RenderAreaManager::loadShapes] requesting shapes from webservice";
    client.GetRenderArea();
}

void RenderAreaManager::saveShapes() {
    std::string renderedShapeData = parse.ShapesToJson(renderedShapes);
    client.PostRenderArea(renderedShapeData);
}

//=========================================== SLOTS ===================================================

void RenderAreaManager::onGoodGetResponse(const QString &json) {
    qDebug().noquote().nospace() << "[RenderAreaManager::onGoodGetResponse] data retrieved";
    std::string jsonStr = json.toStdString();
    renderedShapes = parse.JsonToShapes(jsonStr);
    emit statusMessage("Shapes loaded successfully.");
    emit renderAreaChanged();
}

void RenderAreaManager::onBadGetResponse(const QString &errorMsg) {
    qDebug().noquote().nospace() << "[RenderAreaManager::onBadGetResponse] errorMsg=\"" << errorMsg << "\"";
    emit statusMessage("Error in receiving data: " + errorMsg);
}

void RenderAreaManager::onGoodPostResponse() {
    emit statusMessage("Shapes saved successfully.");
}

void RenderAreaManager::onBadPostResponse(const QString &errorMsg) {
    qDebug().noquote().nospace() << "[RenderAreaManager::onBadPostResponse] errorMsg=\"" << errorMsg << "\"";
    emit statusMessage("Error in saving shapes: " + errorMsg);
}

void RenderAreaManager::onGoodDeleteResponse() {
    qDebug().noquote().nospace() << "[RenderAreaManager::onGoodDeleteResponse] delete_all_success";
    emit statusMessage("All shapes deleted successfully.");
}

void RenderAreaManager::onBadDeleteResponse(const QString &errorMsg) {
    qDebug().noquote().nospace() << "[RenderAreaManager::onBadDeleteResponse] errorMsg=\"" << errorMsg << "\"";
    emit statusMessage("Error in deleting shapes: " + errorMsg);
}
