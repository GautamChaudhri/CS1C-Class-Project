#include "RenderAreaManager.h"
#include <QString>

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
    renderedShapes.push_back(shape);
    emit renderAreaChanged();
    saveShapes();
}



void RenderAreaManager::modifyShape(Shape* shape, QString key, int value) {
    int shapeId = shape->getShapeId();
    int targetId = shape->getTrackerId();

    switch (shapeId) {
        case LINE:
        {
            Line* line = static_cast<Line*>(shape);

            if (key == "X:")
            {
                // Move entire line to new anchor X
                line->Move(value, line->getY());
            }
            else if (key == "Y:")
            {
                // Move entire line to new anchor Y
                line->Move(line->getX(), value);
            }
            else if (key == "X2:")
            {
                // Update the end-point X coordinate
                QPoint endPoint = line->getEndPoint();
                endPoint.setX(value);
                line->setEndPoint(endPoint);
            }
            else if (key == "Y2:")
            {
                // Update the end-point Y coordinate
                QPoint endPoint = line->getEndPoint();
                endPoint.setY(value);
                line->setEndPoint(endPoint);
            }

            emit renderAreaChanged();
            break;
        }
        case POLYLINE:
        {
            Polyline* polyline = static_cast<Polyline*>(shape);

            if (key == "X:")
            {
                // Move entire polyline by delta X
                polyline->Move(value, polyline->getY());
            }
            else if (key == "Y:")
            {
                // Move entire polyline by delta Y
                polyline->Move(polyline->getX(), value);
            }
            else
            {
                // handle edits to specific points: "X2:", "Y2:", etc.
                QPolygon points = polyline->getPointsList();
                if (key.startsWith("X"))
                {
                    // extract the point index from the key (e.g., "X3:" → index 2)
                    int pointIndex = key.mid(1, key.length() - 2).toInt() - 1;
                    if (pointIndex >= 0 && pointIndex < points.size())
                    {
                        points[pointIndex].setX(value);
                    }
                }
                else if (key.startsWith("Y"))
                {
                    int pointIndex = key.mid(1, key.length() - 2).toInt() - 1;
                    if (pointIndex >= 0 && pointIndex < points.size())
                    {
                        points[pointIndex].setY(value);
                    }
                }
                polyline->setPointsList(points);
            }

            emit renderAreaChanged();
            break;
        }
        case POLYGON:
        {
            Polygon* polygon = static_cast<Polygon*>(shape);

            if (key == "X:")
            {
                // Move entire polygon by delta X
                polygon->Move(value, polygon->getY());
            }
            else if (key == "Y:")
            {
                // Move entire polygon by delta Y
                polygon->Move(polygon->getX(), value);
            }
            else
            {
                // handle edits to specific points
                QPolygon points = polygon->getPointsList();
                if (key.startsWith("X"))
                {
                    int pointIndex = key.mid(1, key.length() - 2).toInt() - 1;
                    if (pointIndex >= 0 && pointIndex < points.size())
                    {
                        points[pointIndex].setX(value);
                    }
                }
                else if (key.startsWith("Y"))
                {
                    int pointIndex = key.mid(1, key.length() - 2).toInt() - 1;
                    if (pointIndex >= 0 && pointIndex < points.size())
                    {
                        points[pointIndex].setY(value);
                    }
                }
                polygon->setPointsList(points);
            }

            emit renderAreaChanged();
            break;
        }
        case RECTANGLE:
        {
            Rectangle* pRectangle = static_cast<Rectangle*>(shape);
            if (key == "X:") {
                pRectangle->setX(value);
            }
            else if (key == "Y:") {
                pRectangle->setY(value);
            }
            else if (key == "Length:") {
                pRectangle->setLength(value);
            }
            else if (key == "Width:") {
                pRectangle->setWidth(value);
            }
            emit renderAreaChanged();
            break;
        }
        case SQUARE:
        {
            Square* pSquare = static_cast<Square*>(shape);
            if (key == "X:") {
                pSquare->setX(value);
            }
            else if (key == "Y:") {
                pSquare->setY(value);
            }
            else if (key == "Length:") {
                pSquare->setLength(value);
            }
            emit renderAreaChanged();
            break;
        }
        case ELLIPSE:
        {
            Ellipse* pEllipse = static_cast<Ellipse*>(shape);
            if (key == "X:") {
                pEllipse->setX(value);
            }
            else if (key == "Y:") {
                pEllipse->setY(value);
            }
            else if (key == "Semi-Minor Axis:") {
                pEllipse->setA(value);
            }
            else if (key == "Semi-Major Axis:") {
                pEllipse->setB(value);
            }
            emit renderAreaChanged();
            break;
        }
        case CIRCLE:
        {
            Circle* pCircle = static_cast<Circle*>(shape);
            if (key == "X:") {
                pCircle->setX(value);
            }
            else if (key == "Y:") {
                pCircle->setY(value);
            }
            else if (key == "Length:") {
                pCircle->setR(value);
            }
            emit renderAreaChanged();
            break;
        }
        case TEXT:
        {
            Text* pText = static_cast<Text*>(shape);
            if (key == "X:") {
                pText->setX(value);
            }
            else if (key == "Y:") {
                pText->setY(value);
            }
            else if (key == "Length:") {
                pText->setLength(value);
            }
            else if (key == "Width:") {
                pText->setWidth(value);
            }
            emit renderAreaChanged();
            break;
        }
        default:
            qDebug() << "[RenderAreaManager::modifyShape] Unknown shape type. ShapeId: " << shapeId;
            return;
    }
    saveShapes();
}



void RenderAreaManager::deleteShape(const int trackerId) {
    bool shapeFound = false;

    for (size_t i = 0; i < renderedShapes.size() && !shapeFound; ++i) {
        if (renderedShapes[i]->getTrackerId() == trackerId) {
            delete renderedShapes[i];
            renderedShapes.erase(renderedShapes.begin() + i);
            emit renderAreaChanged();
            saveShapes();
        }
    }

    if (!shapeFound) {
        QString message = "Shape not found. TrackerId: " + trackerId;
        emit renderAreaNotChanged(message);
    }
}



void RenderAreaManager::deleteAllShapes() {
    for (Shape* shape : renderedShapes)
        delete shape;
    emit renderAreaChanged();
    //renderedShapes.clear();
    client.DeleteShapesAll();
}



void RenderAreaManager::loadShapes() {
    client.GetRenderArea();
    emit renderAreaChanged();
}



void RenderAreaManager::saveShapes() {
    std::string renderedShapeData = parse.ShapesToJson(renderedShapes);
    client.PostRenderArea(renderedShapeData);
}



void RenderAreaManager::onGoodGetResponse(const QString &json) {
    std::string jsonStr = json.toStdString();
    renderedShapes = parse.JsonToShapes(jsonStr);
    emit statusMessage("Shapes loaded successfully.");
    emit renderAreaChanged();
}



void RenderAreaManager::onBadGetResponse(const QString &errorMsg) {
    emit statusMessage("Error in receiving data: " + errorMsg);
}



void RenderAreaManager::onGoodPostResponse() {
    emit statusMessage("Shapes saved successfully.");
}



void RenderAreaManager::onBadPostResponse(const QString &errorMsg) {
    emit statusMessage("Error in saving shapes: " + errorMsg);
}



void RenderAreaManager::onGoodDeleteResponse() {
    emit statusMessage("All shapes deleted successfully.");
}



void RenderAreaManager::onBadDeleteResponse(const QString &errorMsg) {
    emit statusMessage("Error in deleting shapes: " + errorMsg);
}
