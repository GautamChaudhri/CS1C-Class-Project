#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QDialog>
#include <QStackedWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>

/**
 * @brief The LoginWindow class
 */
class LoginWindow : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief LoginWindow Constructor
     * @param parent - QWidget of which this class belongs to
     */
    explicit LoginWindow(QWidget *parent = nullptr);

    /**
     * @brief username - Returns the username
     * @return
     */
    QString username() const;

    /**
     * @brief password - Returns the password
     * @return
     */
    QString password() const;

signals:
    /**
     * @brief loginRequested - Handles when a login is requested
     * @param username - The user's username
     * @param password - The user's password
     */
    void loginRequested(const QString &username, const QString &password);

    /**
     * @brief signupRequested - Handles when a user is signing up
     * @param username - The user's username
     * @param password - The user's password
     * @param admin - Boolean depicting whether the user is an admin or not
     */
    void signupRequested(const QString &username, const QString &password, const bool admin);

private slots:
    /**
     * @brief showSignupPage - Displays the signup page
     */
    void showSignupPage();

    /**
     * @brief showLoginPage - Displays the login page
     */
    void showLoginPage();

    /**
     * @brief attemptLogin - Verifies if the login is valid
     */
    void attemptLogin();

    /**
     * @brief attemptSignup - Verifies if the signup is valid
     */
    void attemptSignup();

private:
    QStackedWidget *stack; ///< Stack for layout of widgets

    ///< --- login page widgets
    QWidget *loginPage;
    QLineEdit *loginUserEdit;
    QLineEdit *loginPassEdit;
    QPushButton *loginBtn;
    QPushButton *toSignupBtn;

    ///< --- signup page widgets
    QWidget *signupPage;
    QLineEdit *signupUserEdit;
    QLineEdit *signupPassEdit;
    QPushButton *signupBtn;
    QPushButton *backToLoginBtn;
};

#endif // LOGINDIALOG_H
