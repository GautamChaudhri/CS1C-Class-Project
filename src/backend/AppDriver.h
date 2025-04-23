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
    /// @brief These slots connect the shapes box UI to the ShapesManager data
    void onShapeAdded(Shape* shape);
    void onShapeChanged(Shape* shape);
    void onShapeDeleted(const int trackerId);
    void onDeleteAllShapes();

    /// @brief These slots connect the render area UI to the RenderAreaManager data
    void onRenderShapeAdded(Shape* shape);
    void onRenderAreaChanged(Shape* shape);
    void onRenderShapeDeleted(const int trackerId);
    void onRenderDeleteAllShapes();

    ///@brief These slots connect the user login UI to the UserManager data
    void onNewUser(const QString username, const QString password, const bool admin);
    void onUserModified(const QString username, const QString password, const bool admin);
    void onUserDeleted(const QString username);
    void onDeleteAllUsers();
    void onLoginAttempt(const QString username, const QString password);


private:
    ShapesManager* shapes;
    RenderAreaManager* renderedShapes;
    UserManager* user;

    MainWindow* mainwindow;
    const RenderArea* renderArea;

    //Subroutines
    void connectFrontendToDriver();
    void connectManagersToFrontend();
};

#endif // APP_DRIVER_H