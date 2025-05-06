///@file ApiClient.cpp
#include "ApiClient.h"

ApiClient::ApiClient(QObject* parent) : QObject{parent}, manager{new QNetworkAccessManager(this)} 
{
    // Catch all finished replies in one place
    connect(manager, &QNetworkAccessManager::finished,
            this, &ApiClient::AnalyzeGetReply);
}



void ApiClient::GetShapes() {
    qDebug().noquote().nospace() << "[ApiClient::GetShapes] url=" << "http://localhost:8080/shapes";
    QNetworkRequest request(QUrl("http://localhost:8080/shapes"));
    auto* reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzeGetReply);
}

void ApiClient::PostShapes(std::string json) {
    QNetworkRequest request(QUrl("http://localhost:8080/shapes"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QString qstr = QString::fromStdString(json);
    auto* reply = manager->post(request, qstr.toUtf8());
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzePostReply);
}

void ApiClient::DeleteShapesAll() {
    QNetworkRequest request(QUrl("http://localhost:8080/shapes-all"));
    auto* reply = manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzeDeleteReply);
}



void ApiClient::GetRenderArea() {
    qDebug().noquote().nospace() << "[ApiClient::GetRenderArea] url=" << "http://localhost:8080/render_area";
    QNetworkRequest request(QUrl("http://localhost:8080/render_area"));
    auto* reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzeGetReply);
}

void ApiClient::PostRenderArea(std::string json) {
    QNetworkRequest request(QUrl("http://localhost:8080/render_area"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QString qstr = QString::fromStdString(json);
    auto* reply = manager->post(request, qstr.toUtf8());
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzePostReply);
}

void ApiClient::DeleteRenderAreaAll() {
    QNetworkRequest request(QUrl("http://localhost:8080/render_area-all"));
    auto* reply = manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzeDeleteReply);
}



void ApiClient::GetUsers() {
    qDebug().noquote().nospace() << "[ApiClient::GetUsers] url=" << "http://localhost:8080/users";
    QNetworkRequest request(QUrl("http://localhost:8080/users"));
    auto* reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzeGetReply);
}

void ApiClient::PostUsers(std::string json) {
    QNetworkRequest request(QUrl("http://localhost:8080/users"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QString qstr = QString::fromStdString(json);
    auto* reply = manager->post(request, qstr.toUtf8());
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzePostReply);
}

void ApiClient::DeleteUsersAll() {
    QNetworkRequest request(QUrl("http://localhost:8080/users-all"));
    auto* reply = manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzeDeleteReply);
}



void ApiClient::GetTestimonials() {
    qDebug().noquote().nospace() << "[ApiClient::GetTestimonials] url=" << "http://localhost:8080/testimonials";
    QNetworkRequest request(QUrl("http://localhost:8080/testimonials"));
    auto* reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzeGetReply);
}

void ApiClient::PostTestimonials(std::string json) {
    QNetworkRequest request(QUrl("http://localhost:8080/testimonials"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QString qstr = QString::fromStdString(json);
    auto* reply = manager->post(request, qstr.toUtf8());
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzePostReply);
}

void ApiClient::DeleteTestimonialsAll() {
    QNetworkRequest request(QUrl("http://localhost:8080/testimonials"));
    auto* reply = manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::AnalyzeDeleteReply);
}

//=========================================== SLOTS ===================================================

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
        qDebug().noquote().nospace() << "[ApiClient::AnalyzeGetReply] failure error_string=\"" << errorStr << "\"";
        emit BadGetReply(errorStr);
    }
    
    reply->deleteLater();
}

void ApiClient::AnalyzePostReply() {
    auto* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply)
        return;
    
    if (reply->error() == QNetworkReply::NoError) {
        // QByteArray bytes = reply->readAll(); // Post replies might not always have a body or it might not be needed
        // QString json = QString::fromUtf8(bytes);
        emit GoodPostReply();
    }
    else {
        QString errorStr = reply->errorString();
        qDebug().noquote().nospace() << "[ApiClient::AnalyzePostReply] failure error_string=\"" << errorStr << "\"";
        emit BadPostReply(errorStr);
    }
    
    reply->deleteLater();
}

void ApiClient::AnalyzeDeleteReply() {
    auto* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply)
        return;
    
    if (reply->error() == QNetworkReply::NoError) {
        // QByteArray bytes = reply->readAll(); // Delete replies might not always have a body
        // QString json = QString::fromUtf8(bytes);
        emit GoodDeleteReply();
    }
    else {
        QString errorStr = reply->errorString();
        qDebug().noquote().nospace() << "[ApiClient::AnalyzeDeleteReply] failure error_string=\"" << errorStr << "\"";
        emit BadDeleteReply(errorStr);
    }
    
    reply->deleteLater();
}