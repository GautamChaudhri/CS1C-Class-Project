#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <QString>
#include <utility>

/**
 * @brief Represents a user account within the application.
 * @details This class encapsulates user credentials (username and password) and
 *          administrative status. It provides constructors, destructors,
 *          copy/move semantics, and getters/setters for its properties.
 */
class UserAccount {
public:
    /**
     * @brief Constructors and Destructor.
     * @details These methods handle the creation, initialization, and destruction
     *          of UserAccount objects.
     */
    UserAccount();                                                      /** @brief Default constructor. Initializes as a guest user. */
    UserAccount(QString username, QString password, bool admin);        /** @brief Parameterized constructor. Initializes with specified credentials and admin status. */
    ~UserAccount();                                                     /** @brief Destructor. */

    /**
     * @brief Copy and Move semantics.
     * @details These methods define how UserAccount objects are copied and moved,
     *          ensuring proper resource management.
     */
    UserAccount(const UserAccount& other);                              /** @brief Copy constructor. */
    UserAccount& operator=(const UserAccount& other);                   /** @brief Copy assignment operator. */
    UserAccount(UserAccount&& other) noexcept;                          /** @brief Move constructor. */
    UserAccount& operator=(UserAccount&& other) noexcept;               /** @brief Move assignment operator. */

    /**
     * @brief Public getters for accessing user account data.
     * @details These methods provide read-only access to the private member variables
     *          of the UserAccount object.
     */
    QString getUsername() const;                                        /** @brief Returns the username of the account. */
    QString getPassword() const;                                        /** @brief Returns the password of the account. */
    bool isAdmin() const;                                               /** @brief Returns true if the user has administrative privileges, false otherwise. */

    /**
     * @brief Public setters for modifying user account data.
     * @details These methods allow modification of the username, password,
     *          and administrative status of the UserAccount object.
     */
    void setUsername(const QString& username);                          /** @brief Sets the username for the account. */
    void setPassword(const QString& password);                          /** @brief Sets the password for the account. */
    void setAdmin(bool admin);                                          /** @brief Sets the administrative status for the account. */
    void setUserAccount(const QString& username, const QString& password, bool admin); /** @brief Sets all properties of the user account at once. */

private:
    QString username;                                                   /**< @brief The username associated with the account. */
    QString password;                                                   /**< @brief The password for the account. For guest users, this might be NULL or empty. */
    bool admin;                                                         /**< @brief Flag indicating whether the user has administrative privileges. */
};

#endif // USERACCOUNT_H
