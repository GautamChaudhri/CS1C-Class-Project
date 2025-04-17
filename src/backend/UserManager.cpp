#include "UserManager.h"

UserManager::UserManager(QObject* parent) : QObject{parent}, currUser{new UserAccount}, client{}, parse{} {
    connect(&client, &ApiClient::GoodGetReply, this, &UserManager::onGoodGetResponse);
    connect(&client, &ApiClient::BadGetReply, this, &UserManager::onBadGetResponse);
    connect(&client, &ApiClient::GoodPostReply, this, &UserManager::onGoodPostResponse);
    connect(&client, &ApiClient::BadPostReply, this, &UserManager::onBadPostResponse);
    connect(&client, &ApiClient::GoodDeleteReply, this, &UserManager::onGoodDeleteResponse);
    connect(&client, &ApiClient::BadDeleteReply, this, &UserManager::onBadDeleteResponse);
    client.GetUsers();
}



UserManager::~UserManager() {
    // Destructor that cleans up the UserAccount objects
    for (size_t i = 0; i < users.size(); ++i)
        delete users[i];
}



void UserManager::addUser(const QString username, const QString password, const bool admin) {
    // Adds a new user to the UserManager
    users.push_back(new UserAccount(username, password, admin));
    saveUsers();
}



void UserManager::changeUser(const QString username, const QString password, const bool admin) {
    // Modifies an existing user's credentials and admin status
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i]->getUsername() == username) {
            delete users[i];
            users[i] = new UserAccount(username, password, admin);
            break;
        }
    }
    saveUsers();
}



void UserManager::deleteUser(QString username) {
    // Deletes a user from the UserManager
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i]->getUsername() == username) {
            delete users[i];
            users.erase(users.begin() + i);
            break;
        }
    }
    saveUsers();
}



void UserManager::deleteAllUsers() {
    client.DeleteUsersAll();
}



void UserManager::loadUsers() {
    // Retrieves all users from the webservice
    client.GetUsers();
}



void UserManager::authenticate(const QString username, const QString password) {
    // Authenticates a user based on username and password
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i]->getUsername() == username && users[i]->getPassword() == password) {
            emit userAuthenticated("User authenticated successfully.");
            delete currUser;
            currUser = users[i];
            return;
        }
    }
    emit statusMessage("Authentication failed. Invalid username or password.");
}



void UserManager::saveUsers() {
    std::string userData = parse.UsersToJson(users);
    client.PostUsers(userData);
}



void UserManager::onGoodGetResponse(const std::string &json) {
    users = parse.JsonToUsers(json);
    emit statusMessage("User data retrieved successfully.");
}



void UserManager::onBadGetResponse(const std::string &errorMsg) {
    emit statusMessage("Failed to retrieve user data from database. Error: " + QString::fromStdString(errorMsg));
}



void UserManager::onGoodPostResponse() {
    emit statusMessage("User data saved successfully.");
}



void UserManager::onBadPostResponse(const std::string &errorMsg) {
    emit statusMessage("Failed to save user data to database. Error: " + QString::fromStdString(errorMsg));
}



void UserManager::onGoodDeleteResponse() {
    emit statusMessage("User data deleted successfully.");
}



void UserManager::onBadDeleteResponse(const std::string &errorMsg) {
    emit statusMessage("Failed to delete user data from database. Error: " + QString::fromStdString(errorMsg));
}