//ApiHandler.h
#ifndef API_HANDLER_H
#define API_HANDLER_H
#include "ApiClient.h"

class ApiHandler : public QObject {
    Q_OBJECT
public:
    explicit ApiHandler(QObject* parent = nullptr);
    ~ApiHandler();
    void fetch();
    bool SuccessfulResponse();
    std::string GetData();

protected slots:
    void Success(const QString &json);
    void Failure(const QString &error);

private:
    ApiClient* client;
    bool successfulResponse;
    std::string data;
    
};

#endif //API_HANDLER_H