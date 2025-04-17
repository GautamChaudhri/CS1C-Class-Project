
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
     loadShapes();
 }
 


 ShapesManager::~ShapesManager() {
     for (Shape* shape : shapes) {
         delete shape;
     }
 }
 


 void ShapesManager::addShape(Shape* shape) {
    shapes.push_back(shape);
    emit shapesChanged();
    saveShapes();
 }
 


 void ShapesManager::deleteShape(int trackerId) {
    for (size_t i = 0; i < shapes.size(); ++i) {
        if (shapes[i]->getTrackerId() == trackerId) {
            delete shapes[i];
            shapes.erase(shapes.begin() + i);
            emit shapesChanged();
            break;
        }
    }
    saveShapes();
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
 


 void ShapesManager::onGoodGetResponse(const std::string &json) {
     shapes = parse.JsonToShapes(json);
     emit statusMessage("Shapes loaded successfully.");
     emit shapesChanged();
 }
 


 void ShapesManager::onBadGetResponse(const std::string &errorMsg) {
     emit statusMessage("Error in receiving data from database: " + QString::fromStdString(errorMsg));
 }
 


 void ShapesManager::onGoodPostResponse() {
     emit statusMessage("Shapes saved successfully.");
 }
 


 void ShapesManager::onBadPostResponse(const std::string &errorMsg) {
     emit statusMessage("Error in saving shapes: " + QString::fromStdString(errorMsg));
 }
 


 void ShapesManager::onGoodDeleteResponse() {
     emit statusMessage("All shapes deleted successfully.");
 }
 


 void ShapesManager::onBadDeleteResponse(const std::string &errorMsg) {
     emit statusMessage("Error in deleting shapes: " + QString::fromStdString(errorMsg));
 }