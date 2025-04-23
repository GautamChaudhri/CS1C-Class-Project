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
    renderedShapes.push_back(shape);
    emit renderAreaChanged(&renderedShapes);
}



void RenderAreaManager::modifyShape(Shape* shape) {
    bool shapeFound = false;

    for (size_t i = 0; i < renderedShapes.size() && !shapeFound; ++i) {
        if (renderedShapes[i]->getTrackerId() == shape->getTrackerId()) {
            delete renderedShapes[i];
            renderedShapes[i] = shape;
            emit renderAreaChanged(&renderedShapes);
            saveShapes();
        }
    }

    if (!shapeFound) {
        QString message = "Shape not found. TrackerId: " + shape->getTrackerId();
        emit renderAreaNotChanged(message);
    }
}



void RenderAreaManager::deleteShape(const int trackerId) {
    bool shapeFound = false;

    for (size_t i = 0; i < renderedShapes.size() && !shapeFound; ++i) {
        if (renderedShapes[i]->getTrackerId() == trackerId) {
            delete renderedShapes[i];
            renderedShapes.erase(renderedShapes.begin() + i);
            emit renderAreaChanged(&renderedShapes);
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
    emit renderAreaChanged(&renderedShapes);
    //renderedShapes.clear();
    client.DeleteShapesAll();
}



void RenderAreaManager::loadShapes() {
    client.GetShapes();
    emit renderAreaChanged(&renderedShapes);
}



void RenderAreaManager::saveShapes() {
    std::string renderedShapeData = parse.ShapesToJson(renderedShapes);
    client.PostRenderArea(renderedShapeData);
}



void RenderAreaManager::onGoodGetResponse(const std::string &json) {
    renderedShapes = parse.JsonToShapes(json);
    emit statusMessage("Shapes loaded successfully.");
    emit renderAreaChanged(&renderedShapes);
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