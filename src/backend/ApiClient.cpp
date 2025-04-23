///@file ApiClient.cpp
#include "ApiClient.h"

ApiClient::ApiClient(QObject* parent) : QObject{parent}, manager{new QNetworkAccessManager(this)} {}


//Get Endpoints
void ApiClient::GetShapes() {
    QNetworkRequest request(QUrl("http://localhost:8080/shapes"));
    auto* reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzeGetReply);
}

void ApiClient::GetRenderArea() {
    QNetworkRequest request(QUrl("http://localhost:8080/render_area"));
    auto* reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzeGetReply);
}

void ApiClient::GetUsers() {
    QNetworkRequest request(QUrl("http://localhost:8080/users"));
    auto* reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzeGetReply);
}



//Post Endpoints
void ApiClient::PostShapes(std::string json) {
    QNetworkRequest request(QUrl("http://localhost:8080/shapes"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QString qstr = QString::fromStdString(json);
    auto* reply = manager->post(request, qstr.toUtf8());
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzePostReply);
}

void ApiClient::PostRenderArea(std::string json) {
    QNetworkRequest request(QUrl("http://localhost:8080/render_area"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QString qstr = QString::fromStdString(json);
    auto* reply = manager->post(request, qstr.toUtf8());
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzePostReply);
}

void ApiClient::PostUsers(std::string json) {
    QNetworkRequest request(QUrl("http://localhost:8080/users"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QString qstr = QString::fromStdString(json);
    auto* reply = manager->post(request, qstr.toUtf8());
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzePostReply);
}



//Delete Endpoints
void ApiClient::DeleteShapesAll() {
    QNetworkRequest request(QUrl("http://localhost:8080/shapes-all"));
    auto* reply = manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzeDeleteReply);
}

void ApiClient::DeleteRenderAreaAll() {
    QNetworkRequest request(QUrl("http://localhost:8080/render_area-all"));
    auto* reply = manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzeDeleteReply);
}

void ApiClient::DeleteUsersAll() {
    QNetworkRequest request(QUrl("http://localhost:8080/users-all"));
    auto* reply = manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzeDeleteReply);
}



//Slot Functions
void ApiClient::AnalyzeGetReply() {
    auto* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply)
        return;
    
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        QString json = QString::fromUtf8(bytes);
        emit GoodGetReply(json);
    }
    else {
        QString errorStr = reply->errorString();
        emit BadGetReply(errorStr);
    }
    
    reply->deleteLater();
}

void ApiClient::AnalyzePostReply() {
    auto* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply)
        return;
    
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        QString json = QString::fromUtf8(bytes);
        emit GoodPostReply();
    }
    else {
        QString errorStr = reply->errorString();
        emit BadPostReply(errorStr);
    }
    
    reply->deleteLater();
}

void ApiClient::AnalyzeDeleteReply() {
    auto* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply)
        return;
    
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        QString json = QString::fromUtf8(bytes);
        emit GoodPostReply();
    }
    else {
        QString errorStr = reply->errorString();
        emit BadDeleteReply(errorStr);
    }
    
    reply->deleteLater();
}