#ifndef USER_ACCOUNT_H
#define USER_ACCOUNT_H

#include <QString>

class UserAccount {
public:
    // Constructors
    UserAccount();      //creates a default guest account
    UserAccount(QString username, QString password, bool admin);
    ~UserAccount();

    // Copy and move constructors and assignment operators
    UserAccount(const UserAccount& other);
    UserAccount& operator=(const UserAccount& other);
    UserAccount(UserAccount&& other) noexcept;
    UserAccount& operator=(UserAccount&& other) noexcept;

    //Getters
    QString getUsername() const;
    QString getPassword() const;
    bool isAdmin() const;

    //Setters
    void setUsername(QString& username);
    void setPassword(QString& password);
    void setAdmin(bool admin);
    void setUserAccount(QString& username, QString& password, bool admin);


private:
    QString username;
    QString password;
    bool admin;
};

#endif // USER_ACCOUNT_H