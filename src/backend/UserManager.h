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
     * @brief Constructor and Destructor.
     * @details Handles the initialization and cleanup of the UserManager.
     *          The constructor sets up connections to the ApiClient for handling
     *          responses to user data requests.
     */
    explicit UserManager(QObject* parent = nullptr);    /** @brief Constructor. Initializes ApiClient connections and loads users. */
    ~UserManager();                                     /** @brief Destructor. Cleans up dynamically allocated UserAccount objects. */

    /**
     * @brief Accessor for the current user.
     * @details Provides a reference to the currently authenticated user account.
     */
    UserAccount* getCurrUserRef();                      /** @brief Returns a pointer to the currently authenticated UserAccount object. */

    /**
     * @brief User account management functions.
     * @details These methods provide functionalities to add, modify, delete,
     *          load, save, and authenticate user accounts. Most operations
     *          will trigger signals to update the UI.
     */
    void addUser(const QString username,                /** @brief Adds a new user account and attempts to authenticate. */
                 const QString password, 
                 const bool admin); 
    void modifyUser(const QString username,             /** @brief Modifies an existing user account's details. */
                    const QString password, 
                    const bool admin); 
    void deleteUser(QString username);                  /** @brief Deletes a specific user account by username. */
    void deleteAllUsers();                              /** @brief Deletes all user accounts from the backend. */
    void loadUsers();                                   /** @brief Initiates loading of all user accounts from the webservice. */
    void saveUsers();                                   /** @brief Saves all current user accounts to the webservice. */
    void authenticate(const QString username,           /** @brief Authenticates a user against the loaded user accounts. */
                      const QString password); 
    
signals:
    /**
     * @brief Signals for UI interaction and status updates.
     * @details These signals are emitted to notify the frontend about changes in user data,
     *          authentication status, or general operational messages.
     */
    void userChanged();                                 /** @brief Emitted when the list of users changes (add, modify, delete). */
    void userNotChanged(const QString &message);        /** @brief Emitted when an operation that would change users fails (e.g., user not found, username taken). */
    void statusMessage(const QString &message);         /** @brief Emitted to provide general status updates or error messages. */
    void userAuthenticated(const UserAccount* currUser);/** @brief Emitted upon successful user authentication, providing the authenticated user. */
    void authenticationFailed(const QString &message);  /** @brief Emitted when user authentication fails. */

private slots:
    /**
     * @brief API client response handlers.
     * @details These private slots are connected to signals from the ApiClient
     *          to process the results of network requests related to user data.
     */
    void onGoodGetResponse(const QString &json);        /** @brief Slot called when a GET request for user data succeeds. */
    void onBadGetResponse(const QString &errorMsg);     /** @brief Slot called when a GET request for user data fails. */
    void onGoodPostResponse();                          /** @brief Slot called when a POST request to save user data succeeds. */
    void onBadPostResponse(const QString &errorMsg);    /** @brief Slot called when a POST request to save user data fails. */
    void onGoodDeleteResponse();                        /** @brief Slot called when a DELETE request for user data succeeds. */
    void onBadDeleteResponse(const QString &errorMsg);  /** @brief Slot called when a DELETE request for user data fails. */
    
private:
    //Data Members
    UserAccount* currUser;                              /**< @brief Pointer to the currently authenticated user. Defaults to a guest user. */
    alpha::vector<UserAccount*> users;                  /**< @brief Vector storing pointers to all loaded UserAccount objects. */
    ApiClient client;                                   /**< @brief API client instance for network communication with the user data backend. */
    Parser parse;                                       /**< @brief Parser instance for JSON serialization/deserialization of user data. */
};

#endif // USER_MANAGER_H
