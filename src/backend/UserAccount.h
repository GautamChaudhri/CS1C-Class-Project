#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <QString>
#include <utility> // For std::move

/**
 * @brief Represents a user account within the application.
 * @details This class encapsulates user credentials (username and password) and
 *          administrative status. It provides constructors, destructors,
 *          copy/move semantics, and getters/setters for its properties.
 */
class UserAccount {
public:
    /**
     * @name Constructors and Destructor
     * @brief Manages the lifecycle of UserAccount objects.
     * @details These methods handle the creation, initialization, and destruction
     *          of UserAccount objects.
     */
    /** @{ */
    UserAccount();                                                      ///< Default constructor. Initializes as a guest user.
    UserAccount(QString username, QString password, bool admin);        ///< Parameterized constructor. Initializes with specified credentials and admin status.
    ~UserAccount();                                                     ///< Destructor.
    /** @} */

    /**
     * @name Copy and Move Semantics
     * @brief Defines how UserAccount objects are copied and moved.
     * @details These methods define how UserAccount objects are copied and moved,
     *          ensuring proper resource management.
     */
    /** @{ */
    UserAccount(const UserAccount& other);                              ///< Copy constructor.
    UserAccount& operator=(const UserAccount& other);                   ///< Copy assignment operator.
    UserAccount(UserAccount&& other) noexcept;                          ///< Move constructor.
    UserAccount& operator=(UserAccount&& other) noexcept;               ///< Move assignment operator.
    /** @} */

    /**
     * @name Getters
     * @brief Public getters for accessing user account data.
     * @details These methods provide read-only access to the private member variables
     *          of the UserAccount object.
     */
    /** @{ */
    QString getUsername() const;                                        ///< Returns the username of the account.
    QString getPassword() const;                                        ///< Returns the password of the account.
    bool isAdmin() const;                                               ///< Returns true if the user has administrative privileges, false otherwise.
    /** @} */

    /**
     * @name Setters
     * @brief Public setters for modifying user account data.
     * @details These methods allow modification of the username, password,
     *          and administrative status of the UserAccount object.
     */
    /** @{ */
    void setUsername(const QString& username);                          ///< Sets the username for the account.
    void setPassword(const QString& password);                          ///< Sets the password for the account.
    void setAdmin(bool admin);                                          ///< Sets the administrative status for the account.
    void setUserAccount(const QString& username, const QString& password, bool admin); ///< Sets all properties of the user account at once.
    /** @} */

private:
    /**
     * @name Member Data
     * @brief Private member variables storing user account attributes.
     * @details These variables store the core information for each user account.
     */
    /** @{ */
    QString username;                                                   ///< The username associated with the account.
    QString password;                                                   ///< The password for the account. For guest users, this might be NULL or empty.
    bool admin;                                                         ///< Flag indicating whether the user has administrative privileges.
    /** @} */
};

#endif // USERACCOUNT_H
