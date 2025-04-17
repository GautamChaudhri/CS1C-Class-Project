#include "UserAccount.h"

UserAccount::UserAccount() {
    username = "guest";
    password = NULL;
    admin = false;
}



UserAccount::UserAccount(QString username, QString password, bool admin) {
    this->username = username;
    this->password = password;
    this->admin = admin;
}



UserAccount::~UserAccount() {}



QString UserAccount::getUsername() const {
    return username;
}



QString UserAccount::getPassword() const {
    return password;
}



bool UserAccount::isAdmin() const {
    return admin;
}



void UserAccount::setUsername(QString& username) {
    this->username = username;
}



void UserAccount::setPassword(QString& password) {
    this->password = password;
}



void UserAccount::setAdmin(bool admin) {
    this->admin = admin;
}



void UserAccount::setUserAccount(QString& username, QString& password, bool admin) {
    this->username = username;
    this->password = password;
    this->admin = admin;
}
