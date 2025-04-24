#include <QDebug>
#include "AppDriver.h"
#include <QTimer>

AppDriver::AppDriver(QObject* parent) 
          : QObject{parent}, shapes{new ShapesManager}, renderedShapes{new RenderAreaManager}, 
            user{new UserManager} {}

AppDriver::~AppDriver() {
    delete shapes;
    delete renderedShapes;
    delete user;
}

void AppDriver::run() {
    // Construct the main window and grab its renderArea
    mainWindow = new MainWindow(nullptr,
                    shapes->getShapesRef(),
                    renderedShapes->getShapesRef(),
                    user->getCurrUserRef());
    renderArea = mainWindow->getRenderAreaRef();

    // Connect signals BEFORE loading data
    connectFrontendToDriver();
    connectManagersToFrontend();

    // Finally show the window
    mainWindow->show();

    // // Load all the data (this emits shapesChanged())
    // qDebug() << "AppDriver::run() – calling loadAllData()";
    // loadAllData();
    // qDebug() << "After loadAllData(): ShapesManager vector size =" 
    //          << shapes->getShapesRef()->size();
    // qDebug() << "AppDriver::run() – loadAllData() returned";

    // // In case shapesChanged() fired before we connected, do one explicit populate
    // mainWindow->onShapesChanged();
    // Defer loading until after the event loop starts
    qDebug() << "AppDriver::run() – scheduling loadAllData() after event loop starts";
    QTimer::singleShot(0, this, [this]() {
        qDebug() << "AppDriver: loadAllData() now running";
        loadAllData();
    });
}

void AppDriver::shutdown() {
    shapes->saveShapes();
    renderedShapes->saveShapes();
    user->saveUsers();
}

void AppDriver::loadAllData() {
    shapes->loadShapes();
    renderedShapes->loadShapes();
    user->loadUsers();
}



//=========================================== SLOTS ===================================================

void AppDriver::onShapeAdded(Shape* shape) {
    shapes->addShape(shape);
}

void AppDriver::onShapeChanged(Shape* shape) {
    shapes->modifyShape(shape);
}

void AppDriver::onShapeDeleted(const int trackerId) {
    shapes->deleteShape(trackerId);
}

void AppDriver::onDeleteAllShapes() {
    shapes->deleteAllShapes();
}

void AppDriver::onRenderShapeAdded(Shape* shape) {
    renderedShapes->addShape(shape);
}

void AppDriver::onRenderShapeChanged(Shape* shape) {
    renderedShapes->modifyShape(shape);
}

void AppDriver::onRenderShapeDeleted(const int trackerId) {
    renderedShapes->deleteShape(trackerId);
}

void AppDriver::onRenderDeleteAllShapes() {
    renderedShapes->deleteAllShapes();
}

void AppDriver::onNewUser(const QString username, const QString password, const bool admin) {
    user->addUser(username, password, admin);
}

void AppDriver::onUserModified(const QString username, const QString password, const bool admin) {
    user->modifyUser(username, password, admin);
}

void AppDriver::onUserDeleted(const QString username) {
    user->deleteUser(username);
}

void AppDriver::onDeleteAllUsers() {
    user->deleteAllUsers();
}

void AppDriver::onLoginAttempt(const QString username, const QString password) {
    user->authenticate(username, password);
}

//Connects the signals from frontend to the slots in AppDriver
void AppDriver::connectFrontendToDriver() {
    //for shapes
    // connect(mainWindow, &MainWindow::shapeAdded, this, &AppDriver::onShapeAdded);
    // connect(mainWindow, &MainWindow::shapeChanged, this, &AppDriver::onShapeChanged);
    // connect(mainWindow, &MainWindow::shapeDeleted, this, &AppDriver::onShapeDeleted);
    // connect(mainWindow, &MainWindow::deleteAllShapes, this, &AppDriver::onDeleteAllShapes);
    //for rendered shapes
    connect(mainWindow, &MainWindow::shapeAdded, this, &AppDriver::onRenderShapeAdded);
    connect(mainWindow, &MainWindow::shapeChanged, this, &AppDriver::onRenderShapeChanged);
    connect(mainWindow, &MainWindow::shapeDeleted, this, &AppDriver::onRenderShapeDeleted);
    connect(mainWindow, &MainWindow::deleteAllShapes, this, &AppDriver::onRenderDeleteAllShapes);
    //for user accounts
    // connect(loginWindow, &LoginWindow::userAdded, this, &AppDriver::onNewUser);
    // connect(loginWindow, &LoginWindow::userModified, this, &AppDriver::onUserModified);
    // connect(loginWindow, &LoginWindow::userDeleted, this, &AppDriver::onUserDeleted);
    // connect(loginWindow, &LoginWindow::deleteAllUsers, this, &AppDriver::onDeleteAllUsers);
    // connect(loginWindow, &LoginWindow::loginRequested, this, &AppDriver::onLoginAttempt);
}

//Connects the signals in the Manager Classes to the slots in Frontend
void AppDriver::connectManagersToFrontend() {
    qDebug() << "AppDriver::connectManagersToFrontend() – hooking up shapesChanged → onShapesChanged";
    //for shapes
    connect(shapes, &ShapesManager::shapesChanged, mainWindow, &MainWindow::onShapesChanged);
    connect(shapes, &ShapesManager::shapesNotChanged, mainWindow, &MainWindow::onShapesNotChanged);
    connect(shapes, &ShapesManager::statusMessage, mainWindow, &MainWindow::showShapesStatusMessage);
    //for rendered shapes
    connect(renderedShapes, &RenderAreaManager::renderAreaChanged, mainWindow, &MainWindow::onRenderAreaChanged);
    connect(renderedShapes, &RenderAreaManager::renderAreaNotChanged, mainWindow, &MainWindow::onRenderAreaNotChanged);
    connect(renderedShapes, &RenderAreaManager::statusMessage, mainWindow, &MainWindow::showRenderStatusMessage);
    // Debug: confirm signal arrives in AppDriver
    connect(shapes, &ShapesManager::shapesChanged, this, [this]() {
        qDebug() << "AppDriver: shapesChanged received, manager size ="
                 << shapes->getShapesRef()->size();
    });
    //for user accounts
    // connect(user, &UserManager::userChanged, loginWindow, &LoginWindow::onUsersChanged);
    // connect(user, &UserManager::userNotChanged, loginWindow, &LoginWindow::showStatusMessage);
    // connect(user, &UserManager::userAuthenticated, loginWindow, &LoginWindow::onAuthenticated);
    // connect(user, &UserManager::authenticationFailed, loginWindow, &LoginWindow::showStatusMessage);
    // connect(user, &UserManager::statusMessage, loginWindow, &LoginWindow::showStatusMessage);
    qDebug() << "AppDriver::connectManagersToFrontend() – done connecting";
}