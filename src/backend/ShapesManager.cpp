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
    emit shapesChanged();
    saveShapes();
 }



void ShapesManager::modifyShape(Shape* shape) {
    bool shapeFound = false;

    for (size_t i = 0; i < shapes.size() && !shapeFound; ++i) {
        if (shapes[i]->getTrackerId() == shape->getTrackerId()) {
            delete shapes[i];
            shapes[i] = shape;
            emit shapesChanged();
            saveShapes();
        }
    }

    if (!shapeFound) {
        QString message = "Shape not found. TrackerId: " + shape->getTrackerId();
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
            saveShapes();
        }
    }
    
    if (!shapeFound) {
        QString message = "Shape not found. TrackerId: " + trackerId;
        emit shapesNotChanged(message);
    }
 }
 


 void ShapesManager::deleteAllShapes() {
    for (Shape* shape : shapes) {
        delete shape;
    }
    emit shapesChanged();
    client.DeleteShapesAll();
 }
 


 void ShapesManager::loadShapes() {
    client.GetShapes();
 }
 


 void ShapesManager::saveShapes() {
     std::string renderedShapeData = parse.ShapesToJson(shapes);
     client.PostRenderArea(renderedShapeData);
 }
 


 void ShapesManager::onGoodGetResponse(const QString &json) {
     shapes = parse.JsonToShapes(json.toStdString());
     emit statusMessage("Shapes loaded successfully.");
     emit shapesChanged();
 }
 


 void ShapesManager::onBadGetResponse(const QString &errorMsg) {
     emit statusMessage("Error in receiving data from database: " + errorMsg);
 }
 


 void ShapesManager::onGoodPostResponse() {
     emit statusMessage("Shapes saved successfully.");
 }
 


 void ShapesManager::onBadPostResponse(const QString &errorMsg) {
     emit statusMessage("Error in saving shapes: " + errorMsg);
 }
 


 void ShapesManager::onGoodDeleteResponse() {
     emit statusMessage("All shapes deleted successfully.");
 }
 


 void ShapesManager::onBadDeleteResponse(const QString &errorMsg) {
     emit statusMessage("Error in deleting shapes: " + errorMsg);
 }