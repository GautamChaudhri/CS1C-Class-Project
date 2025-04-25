#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QDialog>
#include <QStackedWidget>
#include <QLineEdit>
#include <QPushButton>

class LoginWindow : public QDialog {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

    QString username() const;
    QString password() const;

signals:
    void loginRequested(const QString &username, const QString &password);
    void signupRequested(const QString &username, const QString &password, const bool admin);

private slots:
    void showSignupPage();
    void showLoginPage();
    void attemptLogin();
    void attemptSignup();

private:
    QStackedWidget *stack;

    // --- login page widgets
    QWidget *loginPage;
    QLineEdit *loginUserEdit;
    QLineEdit *loginPassEdit;
    QPushButton *loginBtn;
    QPushButton *toSignupBtn;

    // --- signup page widgets
    QWidget *signupPage;
    QLineEdit *signupUserEdit;
    QLineEdit *signupPassEdit;
    QPushButton *signupBtn;
    QPushButton *backToLoginBtn;
};

#endif // LOGINDIALOG_H
