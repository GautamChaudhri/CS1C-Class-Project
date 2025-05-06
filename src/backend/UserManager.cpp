#include "UserManager.h"

UserManager::UserManager(QObject* parent) : QObject{parent}, currUser{new UserAccount}, client{}, parse{} {
    connect(&client, &ApiClient::GoodGetReply, this, &UserManager::onGoodGetResponse);
    connect(&client, &ApiClient::BadGetReply, this, &UserManager::onBadGetResponse);
    connect(&client, &ApiClient::GoodPostReply, this, &UserManager::onGoodPostResponse);
    connect(&client, &ApiClient::BadPostReply, this, &UserManager::onBadPostResponse);
    connect(&client, &ApiClient::GoodDeleteReply, this, &UserManager::onGoodDeleteResponse);
    connect(&client, &ApiClient::BadDeleteReply, this, &UserManager::onBadDeleteResponse);
    //loadUsers();
}



UserManager::~UserManager() {
    // Destructor that cleans up the UserAccount objects
    for (size_t i = 0; i < users.size(); ++i)
        delete users[i];
}



UserAccount* UserManager::getCurrUserRef() {
    return currUser;
}



void UserManager::addUser(const QString username, const QString password, const bool admin) {
    qDebug().noquote().nospace() << "[UserManager::addUser] adding user=" << username;
    // Adds a new user to the UserManager
    bool userFound = false;
    for (size_t i = 0; i < users.size() && !userFound; ++i) {
        if (users[i]->getUsername() == username) {
            qDebug().noquote().nospace() << "[UserManager::addUser] username is taken: " << username;
            userFound = true;
            emit userNotChanged("Failed to create account! Username already exists.");
            
        }
    }
    if (!userFound) {
        users.push_back(new UserAccount(username, password, admin));
        saveUsers();
        authenticate(username, password);
        qDebug().noquote().nospace() << "[UserManager::addUser] user added successfully";
    }
}



void UserManager::modifyUser(const QString username, const QString password, const bool admin) {
    bool userFound = false;
    for (size_t i = 0; i < users.size() && !userFound; ++i) {
        if (users[i]->getUsername() == username) {
            qDebug().noquote().nospace() << "[UserManager::modifyUser] user found, updating user=" << username;
            delete users[i];
            users[i] = new UserAccount(username, password, admin);
            userFound = true;
            saveUsers();
        }
    }
    if (!userFound) {
        qDebug().noquote().nospace() << "[UserManager::modifyUser] user not found: " << username;
        QString message = "User not found. Username: " + username;
        emit userNotChanged(message);
    }
}



void UserManager::deleteUser(QString username) {
    bool userFound = false;
    for (size_t i = 0; i < users.size() && !userFound; ++i) {
        if (users[i]->getUsername() == username) {
            qDebug().noquote().nospace() << "[UserManager::deleteUser] user found and deleted user=" << username;
            delete users[i];
            users.erase(users.begin() + i);
            userFound = true;
            saveUsers();
        }
    }
    if (!userFound) {
        qDebug().noquote().nospace() << "[UserManager::deleteUser] user not found: " << username;
        QString message = "User not found. Username: " + username;
        emit userNotChanged(message);
    }
}



void UserManager::deleteAllUsers() {
    client.DeleteUsersAll();
    for (size_t i = 0; i < users.size(); ++i) {
        delete users[i];
    }
    //users.clear();
    qDebug().noquote().nospace() << "[UserManager::deleteAllUsers] local user list cleared";
}



void UserManager::loadUsers() {
    qDebug().noquote().nospace() << "[UserManager::loadUsers] requesting user data from webservice";
    // Retrieves all users from the webservice
    client.GetUsers();
}



void UserManager::authenticate(const QString username, const QString password) {
    // Authenticates a user based on username and password
    bool authSuccess = false;
    for (size_t i = 0; i < users.size() && !authSuccess; ++i) {
        if (users[i]->getUsername() == username && users[i]->getPassword() == password) {
            qDebug().noquote().nospace() << "[UserManager::authenticate] success for user: " << username;
            authSuccess = true;
            delete currUser;
            currUser = users[i];
            emit userAuthenticated(currUser);
        }
    }
    if (!authSuccess) {
        qDebug().noquote().nospace() << "[UserManager::authenticate] failed for user: " << username;
        QString message = "Authentication failed. Invalid username or password.";
        emit authenticationFailed(message);
    }
}



void UserManager::saveUsers() {
    std::string userData = parse.UsersToJson(users);
    client.PostUsers(userData);
}



void UserManager::onGoodGetResponse(const QString &json) {
    qDebug().noquote().nospace() << "[UserManager::onGoodGetResponse] user data retrieved";
    std::string str = json.toStdString();
    users = parse.JsonToUsers(str);
    emit statusMessage("User data retrieved successfully.");
}



void UserManager::onBadGetResponse(const QString &errorMsg) {
    qDebug().noquote().nospace() << "[UserManager::onBadGetResponse] error=" << errorMsg;
    emit statusMessage("Failed to retrieve user data from database. Error: " + errorMsg);
}



void UserManager::onGoodPostResponse() {
    qDebug().noquote().nospace() << "[UserManager::onGoodPostResponse] user data saved successfully";
    emit statusMessage("User data saved successfully.");
}



void UserManager::onBadPostResponse(const QString &errorMsg) {
    qDebug().noquote().nospace() << "[UserManager::onBadPostResponse] error=" << errorMsg;
    emit statusMessage("Failed to save user data to database. Error: " + errorMsg);
}



void UserManager::onGoodDeleteResponse() {
    emit statusMessage("User data deleted successfully.");
}



void UserManager::onBadDeleteResponse(const QString &errorMsg) {
    qDebug().noquote().nospace() << "[UserManager::onBadDeleteResponse] error=" << errorMsg;
    emit statusMessage("Failed to delete user data from database. Error: " + errorMsg);
}
