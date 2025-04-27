// loginwindow.cpp
#include "loginwindow.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Login");

    stack = new QStackedWidget(this);

    // --- build login page ---
    loginPage = new QWidget;
    {
        auto *form = new QFormLayout;
        loginUserEdit = new QLineEdit;
        loginPassEdit = new QLineEdit;
        loginPassEdit->setEchoMode(QLineEdit::Password);
        form->addRow("Username:", loginUserEdit);
        form->addRow("Password:", loginPassEdit);

        loginBtn    = new QPushButton("Log In");
        toSignupBtn = new QPushButton("Sign Up");

        auto *btnLay = new QHBoxLayout;
        btnLay->addWidget(loginBtn);
        btnLay->addWidget(toSignupBtn);

        auto *v = new QVBoxLayout(loginPage);
        v->addLayout(form);
        v->addLayout(btnLay);
    }

    // --- build signup page ---
    signupPage = new QWidget;
    {
        auto *form = new QFormLayout;
        signupUserEdit = new QLineEdit;
        signupPassEdit = new QLineEdit;
        signupPassEdit->setEchoMode(QLineEdit::Password);
        form->addRow("New Username:", signupUserEdit);
        form->addRow("New Password:", signupPassEdit);

        signupBtn      = new QPushButton("Create Account");
        backToLoginBtn = new QPushButton("Back");

        auto *btnLay = new QHBoxLayout;
        btnLay->addWidget(signupBtn);
        btnLay->addWidget(backToLoginBtn);

        auto *v = new QVBoxLayout(signupPage);
        v->addLayout(form);
        v->addLayout(btnLay);
    }

    // add pages to the stack
    stack->addWidget(loginPage);
    stack->addWidget(signupPage);

    // main layout
    auto *mainLay = new QVBoxLayout(this);
    mainLay->addWidget(stack);

    // --- connections ---
    connect(toSignupBtn,    &QPushButton::clicked, this, &LoginWindow::showSignupPage);
    connect(backToLoginBtn, &QPushButton::clicked, this, &LoginWindow::showLoginPage);
    connect(loginBtn,       &QPushButton::clicked, this, &LoginWindow::attemptLogin);
    connect(signupBtn,      &QPushButton::clicked, this, &LoginWindow::attemptSignup);
}

QString LoginWindow::username() const {
    return loginUserEdit->text();
}

QString LoginWindow::password() const {
    return loginPassEdit->text();
}

void LoginWindow::showSignupPage() {
    stack->setCurrentWidget(signupPage);
}

void LoginWindow::showLoginPage() {
    stack->setCurrentWidget(loginPage);
}

void LoginWindow::attemptLogin() {
    emit loginRequested(loginUserEdit->text(), loginPassEdit->text());
}

void LoginWindow::attemptSignup() {
    emit signupRequested(signupUserEdit->text(), signupPassEdit->text(), false);
}
