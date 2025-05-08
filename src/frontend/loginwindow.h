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
 * @brief A dialog window for user login and signup.
 * @details This class provides a QDialog with a QStackedWidget to switch between
 *          a login page and a signup page. It emits signals when a login or signup
 *          attempt is made.
 */
class LoginWindow : public QDialog {
    Q_OBJECT

public:
    /**
     * @name Constructor and Public Accessors
     * @brief Methods for creating and interacting with the LoginWindow.
     * @details Includes the constructor and methods to retrieve user input.
     */
    /** @{ */
    explicit LoginWindow(QWidget *parent = nullptr);    ///< Constructor that sets up the UI components for login and signup.

    QString username() const;                           ///< Returns the username entered in the currently active input field (login or signup).
    QString password() const;                           ///< Returns the password entered in the currently active input field (login or signup).
    /** @} */

signals:
    /**
     * @name User Action Signals
     * @brief Signals emitted based on user interactions within the dialog.
     * @details These signals notify other parts of the application about login or signup attempts.
     */
    /** @{ */
    void loginRequested(const QString &username, const QString &password);      ///< Emitted when the user attempts to log in with the provided credentials.
    void signupRequested(const QString &username, const QString &password, const bool admin); ///< Emitted when the user attempts to sign up with the provided credentials. (Admin flag is currently hardcoded to true in the .cpp).
    /** @} */

private slots:
    /**
     * @name Page Navigation and Action Slots
     * @brief Slots to handle UI events like button clicks.
     * @details These slots manage switching between login/signup pages and triggering login/signup attempts.
     */
    /** @{ */
    void showSignupPage();                              ///< Switches the QStackedWidget to display the signup page.
    void showLoginPage();                               ///< Switches the QStackedWidget to display the login page.
    void attemptLogin();                                ///< Emits the loginRequested signal with current input from login fields.
    void attemptSignup();                               ///< Emits the signupRequested signal with current input from signup fields.
    /** @} */

private:
    /**
     * @name UI Components
     * @brief Private member variables storing pointers to UI widgets.
     * @details These widgets make up the login and signup pages.
     */
    /** @{ */
    QStackedWidget *stack;                              ///< The stacked widget managing the login and signup pages.

    // --- login page widgets ---
    QWidget *loginPage;                                 ///< The widget container for the login page UI elements.
    QLineEdit *loginUserEdit;                           ///< Input field for the username on the login page.
    QLineEdit *loginPassEdit;                           ///< Input field for the password on the login page.
    QPushButton *loginBtn;                              ///< Button to initiate a login attempt.
    QPushButton *toSignupBtn;                           ///< Button to navigate to the signup page.

    // --- signup page widgets ---
    QWidget *signupPage;                                ///< The widget container for the signup page UI elements.
    QLineEdit *signupUserEdit;                          ///< Input field for the username on the signup page.
    QLineEdit *signupPassEdit;                          ///< Input field for the password on the signup page.
    QPushButton *signupBtn;                             ///< Button to initiate a signup attempt.
    QPushButton *backToLoginBtn;                        ///< Button to navigate back to the login page.
    /** @} */
};

#endif // LOGIN_WINDOW_H
