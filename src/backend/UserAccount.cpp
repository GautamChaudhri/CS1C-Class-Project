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



// Copy constructor
UserAccount::UserAccount(const UserAccount& other)
  : username(other.username),
    password(other.password),
    admin(other.admin)
{
}



// Copy assignment
UserAccount& UserAccount::operator=(const UserAccount& other) {
    if (this != &other) {
        username = other.username;
        password = other.password;
        admin = other.admin;
    }
    return *this;
}



// Move constructor
UserAccount::UserAccount(UserAccount&& other) noexcept
  : username(std::move(other.username)),
    password(std::move(other.password)),
    admin(other.admin)
{
    other.admin = false;
}



// Move assignment
UserAccount& UserAccount::operator=(UserAccount&& other) noexcept {
    if (this != &other) {
        username = std::move(other.username);
        password = std::move(other.password);
        admin = other.admin;
        other.admin = false;
    }
    return *this;
}



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
