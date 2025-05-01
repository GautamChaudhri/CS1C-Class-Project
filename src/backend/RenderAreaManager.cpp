#include "RenderAreaManager.h"
#include <QString>
#include <QDebug>
#include <QBrush>
#include <QPen>

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
    qDebug() << "[modifyShape] called for shapeId=" << shape->getShapeId()
             << "  key=\"" << key << "\"  value=" << value;
    
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
            else if (key == "X1:")
            {
                // Update the start-point X coordinate
                QPoint startPoint = line->getStartPoint();
                startPoint.setX(value);
                line->setStartPoint(startPoint);
            }
            else if (key == "Y1:")
            {
                // Update the start-point Y coordinate
                QPoint startPoint = line->getStartPoint();
                startPoint.setY(value);
                line->setStartPoint(startPoint);
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
            else
            {
                 qDebug() << "[RenderAreaManager::modifyShape] Line - key not found:" << key;
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
            else if (key.startsWith("X"))
            {
                // handle edits to specific points: "X2:", "Y2:", etc.
                QPolygon points = polyline->getPointsList();

                // extract the point index from the key (e.g., "X3:" → index 2)
                int pointIndex = key.mid(1, key.length() - 2).toInt() - 1;
                if (pointIndex >= 0 && pointIndex < points.size())
                {
                    points[pointIndex].setX(value);
                }
                polyline->setPointsList(points);
            }
            else if (key.startsWith("Y"))
            {
                QPolygon points = polyline->getPointsList();
                int pointIndex = key.mid(1, key.length() - 2).toInt() - 1;
                if (pointIndex >= 0 && pointIndex < points.size())
                {
                    points[pointIndex].setY(value);
                }
                polyline->setPointsList(points);
            }
            else
            {
                 qDebug() << "[RenderAreaManager::modifyShape] Polyline - key not found:" << key;
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
            else if (key.startsWith("X"))
            {
                // handle edits to specific points
                QPolygon points = polygon->getPointsList();
                int pointIndex = key.mid(1, key.length() - 2).toInt() - 1;
                if (pointIndex >= 0 && pointIndex < points.size())
                {
                    points[pointIndex].setX(value);
                }
                polygon->setPointsList(points);
            }
            else if (key.startsWith("Y"))
            {
                // handle edits to specific points
                QPolygon points = polygon->getPointsList();
                int pointIndex = key.mid(1, key.length() - 2).toInt() - 1;
                if (pointIndex >= 0 && pointIndex < points.size())
                {
                    points[pointIndex].setY(value);
                }
                polygon->setPointsList(points);
            }
            else if (key == "Pen:")
            {
                // add later
            }
            else if (key == "Brush:")
            {
                // Convert the value to brush style and set the new brush style using reference
                shape->setInternalBrush().setStyle(static_cast<Qt::BrushStyle>(value));
            }
            else
            {
                 qDebug() << "[RenderAreaManager::modifyShape] Polygon - key not found:" << key;
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
            else if (key == "Pen:")
            {
                // add later
                shape->setInternalBrush().setStyle(static_cast<Qt::BrushStyle>(value));
            }
            else if (key == "Brush:")
            {
                // Convert the value to brush style and set the new brush style using reference
                shape->setInternalBrush().setStyle(static_cast<Qt::BrushStyle>(value));
            }
            else
            {
                 qDebug() << "[RenderAreaManager::modifyShape] Rectangle - key not found:" << key;
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
            else if (key == "Pen:")
            {
                // add later
            }
            else if (key == "Brush:")
            {
                // Convert the value to brush style and set the new brush style using reference
                shape->setInternalBrush().setStyle(static_cast<Qt::BrushStyle>(value));
            }
            else
            {
                 qDebug() << "[RenderAreaManager::modifyShape] Square - key not found:" << key;
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
            else if (key == "Pen:")
            {
                // add later
            }
            else if (key == "Brush:")
            {
                // Convert the value to brush style and set the new brush style using reference
                shape->setInternalBrush().setStyle(static_cast<Qt::BrushStyle>(value));
            }
            else
            {
                 qDebug() << "[RenderAreaManager::modifyShape] Ellipse - key not found:" << key;
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
            else if (key == "Radius:") {
                pCircle->setR(value);
            }
            else if (key == "Pen:")
            {
                // add later
                shape->setInternalBrush().setStyle(static_cast<Qt::BrushStyle>(value));
            }
            else if (key == "Brush:")
            {
                // Debug before change
                qDebug() << "[modifyShape] Circle brush style before change:"
                         << shape->getBrush().style();
                // Convert the value to brush style and set the new brush style using reference
                shape->setInternalBrush().setStyle(static_cast<Qt::BrushStyle>(value));

                // Debug after change
                qDebug() << "[modifyShape] Circle brush style after change:"
                         << shape->getBrush().style();
            }
            else
            {
                 qDebug() << "[RenderAreaManager::modifyShape] Circle - key not found:" << key;
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
            else if (key == "Text:") {
                // Come back later
                // pText->setText(pText->getChildItems()[4]->text(1)); 
                 qDebug() << "[RenderAreaManager::modifyShape] Text modification needs string value, not int.";
            }
            else
            {
                 qDebug() << "[RenderAreaManager::modifyShape] Text - key not found:" << key;
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
    qDebug().noquote().nospace() << "[RenderAreaManager::deleteShape] deleting trackerId=" << trackerId;
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
    qDebug().noquote().nospace() << "[RenderAreaManager::deleteAllShapes] count=" << renderedShapes.size();
    for (Shape* shape : renderedShapes)
        delete shape;
    emit renderAreaChanged();
    //renderedShapes.clear();
    client.DeleteShapesAll();
    qDebug().noquote().nospace() << "[RenderAreaManager::deleteAllShapes] requested_all_delete";
}



void RenderAreaManager::loadShapes() {
    client.GetRenderArea();
    emit renderAreaChanged();
}



void RenderAreaManager::saveShapes() {
    qDebug().noquote().nospace() << "[RenderAreaManager::saveShapes] posting count=" << renderedShapes.size();
    std::string renderedShapeData = parse.ShapesToJson(renderedShapes);
    client.PostRenderArea(renderedShapeData);
}



void RenderAreaManager::onGoodGetResponse(const QString &json) {
    qDebug().noquote().nospace() << "[RenderAreaManager::onGoodGetResponse] json_length=" << json.size();
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
