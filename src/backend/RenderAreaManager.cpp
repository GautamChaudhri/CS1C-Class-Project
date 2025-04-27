#include "RenderAreaManager.h"
#include <QString>
#include <QDebug>

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
    try {
        std::string renderedShapeData = parse.ShapesToJson(renderedShapes);
        qDebug().noquote().nospace() << "[RenderAreaManager::addShape] posting json_size=" << renderedShapeData.size();
        client.PostRenderArea(renderedShapeData);
    } catch (const std::exception &e) {
        qWarning() << "RenderAreaManager::saveShapes failed:" << e.what();
        qDebug() << "RenderAreaManager::addShape exception:" << e.what();
    }
}



void RenderAreaManager::modifyShape(Shape* shape) {
    qDebug().noquote().nospace() << "[RenderAreaManager::modifyShape] start trackerId=" << shape->getTrackerId();
    bool shapeFound = false;

    for (size_t i = 0; i < renderedShapes.size() && !shapeFound; ++i) {
        if (renderedShapes[i]->getTrackerId() == shape->getTrackerId()) {
            delete renderedShapes[i];
            renderedShapes[i] = shape;
            qDebug().noquote().nospace() << "[RenderAreaManager::modifyShape] modified trackerId=" << shape->getTrackerId();
            emit renderAreaChanged();
            saveShapes();
        }
    }

    if (!shapeFound) {
        qDebug().noquote().nospace() << "[RenderAreaManager::modifyShape] not_found trackerId=" << shape->getTrackerId();
        QString message = "Shape not found. TrackerId: " + shape->getTrackerId();
        emit renderAreaNotChanged(message);
    }
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
        QString message = "Shape not found. TrackerId: " + trackerId;
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
    qDebug().noquote().nospace() << "[RenderAreaManager::loadShapes] request";
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
    qDebug().noquote().nospace() << "[RenderAreaManager::onGoodPostResponse] saved_success";
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