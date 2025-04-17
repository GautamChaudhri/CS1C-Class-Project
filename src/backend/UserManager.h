#ifndef USER_MANAGER_H
#define USER_MANAGER_H
#include <QObject>
#include <QString>
#include <cctype>
#include <string>
#include "ApiClient.h"
#include "Parser.h"
#include "UserAccount.h"
#include "../objects/vector.h"

class UserManager : public QObject {
    Q_OBJECT
public:
        /**
     * @brief Default Constructor
     * 
     * @details This constructor initializes the UserManager object and connects
     *          to the ApiClient signals for handling user data.
     * 
     * @param parent - any QObject to tie this instantiation to ensure automatic deletion
     */
    explicit UserManager(QObject* parent = nullptr);
    ~UserManager();

    /**
     * @brief These functions are used to add, change, delete, and load users
     *        in the UserManager.
     * 
     * @details All of these functions emit the userChanged() signal
     *          to notify the frontend that the user list has changed
     *          and needs to be refreshed except for authenticate().
     */
    void addUser(const QString username, const QString password, const bool admin);
    void changeUser(const QString username, const QString password, const bool admin);
    void deleteUser(QString username);
    void deleteAllUsers();
    void loadUsers();
    void saveUsers();
    

signals:
    /**
     * @details These signals are meant to connect to the User window in the frontend. 
     *          - userChanged(): signal for when the user list changes so the UI can refresh
     *          - statusMessage(): passes status updates (e.g., save/load success or errors)
     *          - userAuthenticated(): notifies when authentication succeeds or fails
     */
    void userChanged();
    void statusMessage(const QString &message);
    void userAuthenticated(const QString &message);


private slots:
    void authenticate(const QString username, const QString password);

    /**
     * @details These slot functions receive signals from the ApiClient class
     *          and handle logic after API responses for user data.
     */
    void onGoodGetResponse(const std::string &json);
    void onBadGetResponse(const std::string &errorMsg);
    void onGoodPostResponse();
    void onBadPostResponse(const std::string &errorMsg);
    void onGoodDeleteResponse();
    void onBadDeleteResponse(const std::string &errorMsg);

    
private:
    //Data Members
    UserAccount* currUser;
    alpha::vector<UserAccount*> users;
    ApiClient client;
    Parser parse;
};

#endif // USER_MANAGER_H