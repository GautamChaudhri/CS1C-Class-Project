#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <cctype>
#include <string>
#include "ApiClient.h"
#include "Parser.h"
#include "UserAccount.h"
#include "../objects/vector.h" // Assuming this is a custom vector implementation

/**
 * @brief Manages user accounts, including creation, authentication, and persistence.
 * @details This class handles all operations related to user accounts, such as adding,
 *          modifying, deleting, and authenticating users. It interacts with an
 *          ApiClient to load and save user data from/to a webservice and uses a
 *          Parser for data serialization/deserialization.
 */
class UserManager : public QObject {
    Q_OBJECT
public:
    /**
     * @name Constructor and Destructor
     * @brief Manages the lifecycle of UserManager objects.
     * @details Handles the initialization and cleanup of the UserManager.
     *          The constructor sets up connections to the ApiClient for handling
     *          responses to user data requests and loads initial user data.
     */
    /** @{ */
    explicit UserManager(QObject* parent = nullptr);    ///< Constructor. Initializes ApiClient connections and loads users.
    ~UserManager();                                     ///< Destructor. Cleans up dynamically allocated UserAccount objects.
    /** @} */

    /**
     * @name Current User Access
     * @brief Accessor for the current user.
     * @details Provides a reference to the currently authenticated user account.
     *          If no user is authenticated, this typically points to a guest account.
     */
    /** @{ */
    UserAccount* getCurrUserRef();                      ///< Returns a pointer to the currently authenticated UserAccount object.
    /** @} */

    /**
     * @name User Account Management
     * @brief Core functions for managing user accounts.
     * @details These methods provide functionalities to add, modify, delete,
     *          load, save, and authenticate user accounts. Most operations
     *          will trigger signals to update the UI or indicate status.
     */
    /** @{ */
    void addUser(const QString username,                ///< Adds a new user account and attempts to authenticate with the new credentials.
                 const QString password, 
                 const bool admin); 
    void modifyUser(const QString username,             ///< Modifies an existing user account's details (password, admin status).
                    const QString password, 
                    const bool admin); 
    void deleteUser(QString username);                  ///< Deletes a specific user account by username.
    void deleteAllUsers();                              ///< Deletes all user accounts from the backend.
    void loadUsers();                                   ///< Initiates loading of all user accounts from the webservice.
    void saveUsers();                                   ///< Saves all current user accounts to the webservice.
    void authenticate(const QString username,           ///< Authenticates a user against the loaded user accounts.
                      const QString password); 
    /** @} */
    
signals:
    /**
     * @name User Status Signals
     * @brief Signals for UI interaction and status updates.
     * @details These signals are emitted to notify the frontend about changes in user data,
     *          authentication status, or general operational messages.
     */
    /** @{ */
    void userChanged();                                 ///< Emitted when the list of users changes (add, modify, delete).
    void userNotChanged(const QString &message);        ///< Emitted when an operation that would change users fails (e.g., user not found, username taken).
    void statusMessage(const QString &message);         ///< Emitted to provide general status updates or error messages.
    void userAuthenticated(const UserAccount* currUser);///< Emitted upon successful user authentication, providing the authenticated user.
    void authenticationFailed(const QString &message);  ///< Emitted when user authentication fails.
    /** @} */

private slots:
    /**
     * @name API Response Slots
     * @brief API client response handlers.
     * @details These private slots are connected to signals from the ApiClient
     *          to process the results of network requests related to user data.
     */
    /** @{ */
    void onGoodGetResponse(const QString &json);        ///< Slot called when a GET request for user data succeeds.
    void onBadGetResponse(const QString &errorMsg);     ///< Slot called when a GET request for user data fails.
    void onGoodPostResponse();                          ///< Slot called when a POST request to save user data succeeds.
    void onBadPostResponse(const QString &errorMsg);    ///< Slot called when a POST request to save user data fails.
    void onGoodDeleteResponse();                        ///< Slot called when a DELETE request for user data succeeds.
    void onBadDeleteResponse(const QString &errorMsg);  ///< Slot called when a DELETE request for user data fails.
    /** @} */
    
private:
    /**
     * @name Member Data
     * @brief Private member variables for UserManager.
     * @details These members store the current user, all known users, and utility objects.
     */
    /** @{ */
    UserAccount* currUser;                              ///< Pointer to the currently authenticated user. Defaults to a guest user.
    alpha::vector<UserAccount*> users;                  ///< Vector storing pointers to all loaded UserAccount objects.
    ApiClient client;                                   ///< API client instance for network communication with the user data backend.
    Parser parse;                                       ///< Parser instance for JSON serialization/deserialization of user data.
    /** @} */
};

#endif // USER_MANAGER_H
