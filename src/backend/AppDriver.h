#ifndef APP_DRIVER_H
#define APP_DRIVER_H
#include <QCoreApplication>
#include <QApplication>
#include <QObject>
#include "ShapesManager.h"
#include "RenderAreaManager.h"
#include "UserManager.h"
#include "../frontend/mainwindow.h"
#include "../frontend/renderarea.h"

class AppDriver : public QObject {
    Q_OBJECT
public:
    AppDriver(QObject* parent = nullptr);
    ~AppDriver();

    void run();
    void shutdown();

    void loadAllData();


private slots:
    /// @brief These slots connect the render area UI to the RenderAreaManager data
    // For when a new shape is added to the render area
    void onRenderShapeAdded(Shape* shape);
    // For when an existing shape is modified in the render area
    void onRenderShapeChanged(Shape* shape);
    // For when a single shape is deleted from the render area
    void onRenderShapeDeleted(const int trackerId);
    // For when all shapes are deleted from the render area
    void onRenderDeleteAllShapes();

    /// @brief These slots connect the user login UI to the UserManager data
    // For when a new user is created
    void onNewUser(const QString username, const QString password, const bool admin);
    // For when an existing user's login credentials are modified
    void onUserModified(const QString username, const QString password, const bool admin);
    // For when a single user is deleted
    void onUserDeleted(const QString username);
    // For when all users are deleted
    void onDeleteAllUsers();
    // For when a user attempts to login
    void onLoginAttempt(const QString username, const QString password);


private:
   // ShapesManager* shapes;                  // Manages all the possible shapes that can be rendered
    RenderAreaManager* renderedShapes;      // Manages all the shapes that are currently rendered
    UserManager* user;                      // Manages the current user and holds all existing users to authenticate against     

    MainWindow* mainWindow;
    RenderArea* renderArea;

    //Subroutines
    void connectFrontendToDriver();
    void connectManagersToFrontend();
};

#endif // APP_DRIVER_H
