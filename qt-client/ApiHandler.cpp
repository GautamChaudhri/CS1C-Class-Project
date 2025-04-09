//ApiHandler.cpp
#include "ApiHandler.h"

ApiHandler::ApiHandler(QObject* parent) : QObject{parent}, client{new ApiClient} {}

ApiHandler::~ApiHandler() {
    delete client;
}

void ApiHandler::fetch() {
    client->FetchAllShapes();
    QObject::connect(client, &ApiClient::ShapesJsonReceived, this, &ApiHandler::Success);
    QObject::connect(client, &ApiClient::ErrorOccurred, this, &ApiHandler::Failure);
}

bool ApiHandler::SuccessfulResponse() {
    return successfulResponse;
}

std::string ApiHandler::GetData() {
    return data;
}

void ApiHandler::Success(const QString &json) {
    successfulResponse = true;
    data = json.toStdString();
}

void ApiHandler::Failure(const QString &errorMsg) {
    successfulResponse = false;
    data = errorMsg.toStdString();
}