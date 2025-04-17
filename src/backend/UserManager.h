#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <QObject>
#include <QString>
#include <cctype>
#include <string>
#include "UserAccount.h"
#include "Parser.h"
#include "ApiClient.h"
#include "../objects/vector.h"

class UserManager : public QObject {
    Q_OBJECT
public:
    explicit UserManager(QObject* parent = nullptr);
    ~UserManager();

    void addUser(const QString username, const QString password, const bool admin);
    void deleteUser(QString username);
    void deleteAllUsers();
    UserAccount* authenticate(const QString username, const QString password);

private slots:
    //For Api Client
    void onGoodGetResponse(const std::string &json);
    void onBadGetResponse(const std::string &errorMsg);
    void onGoodPostResponse();
    void onBadPostResponse(const std::string &errorMsg);
    void onGoodDeleteResponse();
    void onBadDeleteResponse(const std::string &errorMsg);

private:
    //Data Members
    alpha::vector<UserAccount*> users;
    ApiClient client;
    Parser parse;

    //Subroutines
    void saveUserData();

};

#endif // USER_MANAGER_H