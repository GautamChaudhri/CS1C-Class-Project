///@file ApiClient.cpp
#include "ApiClient.h"

//ApiClient::ApiClient(QObject* parent) : QObject{parent}, manager{new QNetworkAccessManager(this)} {}
ApiClient::ApiClient(QObject* parent) : QObject{parent}, manager{new QNetworkAccessManager(this)} 
{
    // Catch all finished replies in one place
    connect(manager, &QNetworkAccessManager::finished,
            this, &ApiClient::AnalyzeGetReply);
}

//Get Endpoints
void ApiClient::GetShapes() {
    qDebug() << "ApiClient::GetShapes() called";
    QNetworkRequest request(QUrl("http://localhost:8080/shapes"));
    auto* reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzeGetReply);
}

void ApiClient::GetRenderArea() {
    qDebug() << "ApiClient::GetRenderArea() called";
    QNetworkRequest request(QUrl("http://localhost:8080/render_area"));
    auto* reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzeGetReply);
}

void ApiClient::GetUsers() {
    qDebug() << "ApiClient::GetUsers() called";
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
    qDebug() << "ApiClient reply finished; HTTP status ="
            << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()
            << "payload size =" << reply->size();
    qDebug() << "ApiClient payload:" << reply->readAll();
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