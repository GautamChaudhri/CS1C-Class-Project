#include <QDebug>
 #include "ShapesManager.h"
 
 ShapesManager::ShapesManager(QObject* parent)
   : QObject(parent), client(), parse()
 {
     connect(&client, &ApiClient::GoodGetReply, this, &ShapesManager::onGoodGetResponse);
     connect(&client, &ApiClient::BadGetReply,  this, &ShapesManager::onBadGetResponse);
     connect(&client, &ApiClient::GoodPostReply, this, &ShapesManager::onGoodPostResponse);
     connect(&client, &ApiClient::BadPostReply, this, &ShapesManager::onBadPostResponse);
     connect(&client, &ApiClient::GoodDeleteReply, this, &ShapesManager::onGoodDeleteResponse);
     connect(&client, &ApiClient::BadDeleteReply,  this, &ShapesManager::onBadDeleteResponse);
     //loadShapes();
 }
 


 ShapesManager::~ShapesManager() {
     for (Shape* shape : shapes) {
         delete shape;
     }
 }

 alpha::vector<Shape*>* ShapesManager::getShapesRef() {
    return &shapes;
}
 


 void ShapesManager::addShape(Shape* shape) {
    shapes.push_back(shape);
    qDebug().noquote().nospace() << "[ShapesManager::addShape] added shape trackerId=" << shape->getTrackerId();
    emit shapesChanged();
    qDebug().noquote().nospace() << "[ShapesManager::addShape] triggering saveShapes, totalShapes=" << shapes.size();
    saveShapes();
 }



void ShapesManager::modifyShape(Shape* shape) {
    bool shapeFound = false;

    for (size_t i = 0; i < shapes.size() && !shapeFound; ++i) {
        if (shapes[i]->getTrackerId() == shape->getTrackerId()) {
            delete shapes[i];
            shapes[i] = shape;
            emit shapesChanged();
            qDebug().noquote().nospace() << "[ShapesManager::modifyShape] replaced shape trackerId=" << shape->getTrackerId();
            saveShapes();
        }
    }

    if (!shapeFound) {
        QString message = "Shape not found. TrackerId: " + shape->getTrackerId();
        qDebug().noquote().nospace() << "[ShapesManager::modifyShape] failed to find shape trackerId=" << shape->getTrackerId();
        emit shapesNotChanged(message);
    }
}



 void ShapesManager::deleteShape(const int trackerId) {
    bool shapeFound = false;

    for (size_t i = 0; i < shapes.size() && !shapeFound; ++i) {
        if (shapes[i]->getTrackerId() == trackerId) {
            delete shapes[i];
            shapes.erase(shapes.begin() + i);
            emit shapesChanged();
            qDebug().noquote().nospace() << "[ShapesManager::deleteShape] deleted shape trackerId=" << trackerId;
            saveShapes();
        }
    }
    
    if (!shapeFound) {
        QString message = "Shape not found. TrackerId: " + trackerId;
        qDebug().noquote().nospace() << "[ShapesManager::deleteShape] no shape found trackerId=" << trackerId;
        emit shapesNotChanged(message);
    }
 }
 


 void ShapesManager::deleteAllShapes() {
    qDebug().noquote().nospace() << "[ShapesManager::deleteAllShapes] deleting all, shapeCount=" << shapes.size();
    for (Shape* shape : shapes) {
        delete shape;
    }
    emit shapesChanged();
    qDebug().noquote().nospace() << "[ShapesManager::deleteAllShapes] local list cleared";
    client.DeleteShapesAll();
 }
 


 void ShapesManager::loadShapes() {
    qDebug().noquote().nospace() << "[ShapesManager::loadShapes] calling client.GetShapes()";
    client.GetShapes();
 }
 


 void ShapesManager::saveShapes() {
    qDebug().noquote().nospace() << "[ShapesManager::saveShapes] preparing to save shapeCount=" << shapes.size();
    std::string renderedShapeData = parse.ShapesToJson(shapes);
    client.PostRenderArea(renderedShapeData);
 }
 


 void ShapesManager::onGoodGetResponse(const QString &json) {
    qDebug().noquote().nospace() << "[ShapesManager::onGoodGetResponse] received JSON response, jsonSize=" << json.size();
    shapes = parse.JsonToShapes(json.toStdString());
    qDebug().noquote().nospace() << "[ShapesManager::onGoodGetResponse] parsed shapeCount=" << shapes.size();

    emit statusMessage("Shapes loaded successfully.");
    emit shapesChanged();
 }
 


 void ShapesManager::onBadGetResponse(const QString &errorMsg) {
    qDebug().noquote().nospace() << "[ShapesManager::onBadGetResponse] error receiving shapes, error=" << errorMsg;
    emit statusMessage("Error in receiving data from database: " + errorMsg);
 }
 


 void ShapesManager::onGoodPostResponse() {
    qDebug().noquote().nospace() << "[ShapesManager::onGoodPostResponse] shapes saved successfully";
    emit statusMessage("Shapes saved successfully.");
 }
 


 void ShapesManager::onBadPostResponse(const QString &errorMsg) {
    qDebug().noquote().nospace() << "[ShapesManager::onBadPostResponse] error saving shapes, error=" << errorMsg;
    emit statusMessage("Error in saving shapes: " + errorMsg);
 }
 


 void ShapesManager::onGoodDeleteResponse() {
    qDebug().noquote().nospace() << "[ShapesManager::onGoodDeleteResponse] all shapes deleted successfully";
    emit statusMessage("All shapes deleted successfully.");
 }
 


 void ShapesManager::onBadDeleteResponse(const QString &errorMsg) {
    qDebug().noquote().nospace() << "[ShapesManager::onBadDeleteResponse] error deleting shapes, error=" << errorMsg;
    emit statusMessage("Error in deleting shapes: " + errorMsg);
 }