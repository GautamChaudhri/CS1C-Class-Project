#include "RenderAreaManager.h"

RenderAreaManager::RenderAreaManager(QObject* parent) : QObject{parent}, client{}, parse{} {
    connect(&client, &ApiClient::GoodGetReply, this, &RenderAreaManager::onGoodGetResponse);
    connect(&client, &ApiClient::BadGetReply, this, &RenderAreaManager::onBadGetResponse);
    connect(&client, &ApiClient::GoodPostReply, this, &RenderAreaManager::onGoodPostResponse);
    connect(&client, &ApiClient::BadPostReply, this, &RenderAreaManager::onBadPostResponse);
    connect(&client, &ApiClient::GoodDeleteReply, this, &RenderAreaManager::onGoodDeleteResponse);
    connect(&client, &ApiClient::BadDeleteReply, this, &RenderAreaManager::onBadDeleteResponse);
    loadShapes();
}



RenderAreaManager::~RenderAreaManager() {
    for (size_t i = 0; i < renderedShapes.size(); ++i)
        delete renderedShapes[i];
}



void RenderAreaManager::addShape(Shape* shape) {
    renderedShapes.push_back(shape);
    emit renderAreaChanged();
}



void RenderAreaManager::changeShape(Shape* shape) {
    // Changes a shape in the RenderAreaManager
    for (size_t i = 0; i < renderedShapes.size(); ++i) {
        if (renderedShapes[i]->getTrackerId() == shape->getTrackerId()) {
            delete renderedShapes[i];
            renderedShapes[i] = shape;
            emit renderAreaChanged();
            break;
        }
    }
}



void RenderAreaManager::deleteShape(int trackerId) {
    // Deletes a shape from the RenderAreaManager
    for (size_t i = 0; i < renderedShapes.size(); ++i) {
        if (renderedShapes[i]->getTrackerId() == trackerId) {
            delete renderedShapes[i];
            renderedShapes.erase(renderedShapes.begin() + i);
            emit renderAreaChanged();
            break;
        }
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
    client.GetShapes();
}



void RenderAreaManager::saveShapes() {
    std::string renderedShapeData = parse.ShapesToJson(renderedShapes);
    client.PostRenderArea(renderedShapeData);
}



void RenderAreaManager::onGoodGetResponse(const std::string &json) {
    renderedShapes = parse.JsonToShapes(json);
    emit statusMessage("Shapes loaded successfully.");
    emit renderAreaChanged();
}



void RenderAreaManager::onBadGetResponse(const std::string &errorMsg) {
    emit statusMessage("Error in receiving data from database: " + QString::fromStdString(errorMsg));
}



void RenderAreaManager::onGoodPostResponse() {
    emit statusMessage("Shapes saved successfully.");
}



void RenderAreaManager::onBadPostResponse(const std::string &errorMsg) {
    emit statusMessage("Error in saving shapes: " + QString::fromStdString(errorMsg));
}



void RenderAreaManager::onGoodDeleteResponse() {
    emit statusMessage("All shapes deleted successfully.");
}



void RenderAreaManager::onBadDeleteResponse(const std::string &errorMsg) {
    emit statusMessage("Error in deleting shapes: " + QString::fromStdString(errorMsg));
}