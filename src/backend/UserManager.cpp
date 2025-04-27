#include "UserManager.h"
#include <QString>

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
    // Adds a new user to the UserManager
    // users.push_back(new UserAccount(username, password, admin));
    // saveUsers();
    // authenticate(username, password);
    bool userFound = false;
    for (size_t i = 0; i < users.size() && !userFound; ++i) {
        if (users[i]->getUsername() == username) {
            userFound = true;
            emit userNotChanged("Failed to create account! Username already exists.");
            
            
            delete users[i];
            users[i] = new UserAccount(username, password, admin);
            
            emit userChanged();
            saveUsers();
        }
    }
    if (!userFound) {
        users.push_back(new UserAccount(username, password, admin));
        saveUsers();
        authenticate(username, password);
    }
}



void UserManager::modifyUser(const QString username, const QString password, const bool admin) {
    bool userFound = false;
    for (size_t i = 0; i < users.size() && !userFound; ++i) {
        if (users[i]->getUsername() == username) {
            delete users[i];
            users[i] = new UserAccount(username, password, admin);
            userFound = true;
            emit userChanged();
            saveUsers();
        }
    }
    if (!userFound) {
        QString message = "User not found. Username: " + username;
        emit userNotChanged(message);
    }
}



void UserManager::deleteUser(QString username) {
    bool userFound = false;
    for (size_t i = 0; i < users.size() && !userFound; ++i) {
        if (users[i]->getUsername() == username) {
            delete users[i];
            users.erase(users.begin() + i);
            userFound = true;
            emit userChanged();
            saveUsers();
        }
    }
    if (!userFound) {
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
    emit userChanged();
}



void UserManager::loadUsers() {
    // Retrieves all users from the webservice
    client.GetUsers();
}



void UserManager::authenticate(const QString username, const QString password) {
    // Authenticates a user based on username and password
    bool authSuccess = false;
    for (size_t i = 0; i < users.size() && !authSuccess; ++i) {
        if (users[i]->getUsername() == username && users[i]->getPassword() == password) {
            authSuccess = true;
            delete currUser;
            currUser = users[i];
            emit userAuthenticated(currUser);
        }
    }
    if (!authSuccess) {
        QString message = "Authentication failed. Invalid username or password.";
        emit authenticationFailed(message);
    }
}



void UserManager::saveUsers() {
    std::string userData = parse.UsersToJson(users);
    client.PostUsers(userData);
}



void UserManager::onGoodGetResponse(const QString &json) {
    std::string str = json.toStdString();
    users = parse.JsonToUsers(str);
    emit statusMessage("User data retrieved successfully.");
}



void UserManager::onBadGetResponse(const QString &errorMsg) {
    emit statusMessage("Failed to retrieve user data from database. Error: " + errorMsg);
}



void UserManager::onGoodPostResponse() {
    emit statusMessage("User data saved successfully.");
}



void UserManager::onBadPostResponse(const QString &errorMsg) {
    emit statusMessage("Failed to save user data to database. Error: " + errorMsg);
}



void UserManager::onGoodDeleteResponse() {
    emit statusMessage("User data deleted successfully.");
}



void UserManager::onBadDeleteResponse(const QString &errorMsg) {
    emit statusMessage("Failed to delete user data from database. Error: " + errorMsg);
}