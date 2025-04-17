#include "UserManager.h"

UserManager::UserManager(QObject* parent) : QObject(parent), client(), parse() {
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
    saveUserData();
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
    saveUserData();
}


void UserManager::deleteAllUsers() {
    client.DeleteUsersAll();
}



UserAccount* UserManager::authenticate(const QString username, const QString password) {
    // Authenticates a user based on username and password
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i]->getUsername() == username && users[i]->getPassword() == password) {
            return users[i];
        }
    }
    return nullptr;
}


void UserManager::saveUserData() {
    std::string userData = parse.UsersToJson(users);
    client.PostUsers(userData);
}




void UserManager::onGoodGetResponse(const std::string &json) {
    users = parse.JsonToUsers(json);
    for (int i = 0; i < users.size(); i++) {
        std::cout << "User: " << users[i]->getUsername().toStdString() << std::endl
                  << "Password: " << users[i]->getPassword().toStdString() << std::endl
                  << "Admin: " << (users[i]->isAdmin() ? "true" : "false") << std::endl;
    }
    std::cout << "User data retrieved successfully!\n\n\n";
}



void UserManager::onBadGetResponse(const std::string &errorMsg) {
    std::cout << "Failed to retrieve user data from database.\nError: " << errorMsg << std::endl;
}



void UserManager::onGoodPostResponse() {
    std::cout << "User data saved successfully!\n";
}



void UserManager::onBadPostResponse(const std::string &errorMsg) {
    std::cout << "Failed to save user data to database.\nError: " << errorMsg << std::endl;
}



void UserManager::onGoodDeleteResponse() {
    std::cout << "User data deleted successfully!\n";
}



void UserManager::onBadDeleteResponse(const std::string &errorMsg) {
    std::cout << "Failed to save delete data to database.\nError: " << errorMsg << std::endl;
}