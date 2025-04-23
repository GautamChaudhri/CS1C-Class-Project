#include "AppDriver.h"

AppDriver::AppDriver(QObject* parent) 
          : QObject{parent}, shapes{new ShapesManager}, renderedShapes{new RenderAreaManager}, 
            user{new UserManager} {
    connectFrontendToDriver();
    connectManagersToFrontend();
}

AppDriver::~AppDriver() {
    delete shapes;
    delete renderedShapes;
    delete user;
}

void AppDriver::run() {
    loadAllData();
    mainwindow = new MainWindow(nullptr, shapes->getShapesRef(), renderedShapes->getShapesRef(), user->getCurrUserRef());
    renderArea = mainwindow->getRenderAreaRef();
    mainwindow->show();
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

void AppDriver::onRenderAreaChanged(Shape* shape) {
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
    // connect(mainwindow, &MainWindow::shapeAdded, this, &AppDriver::onShapeAdded);
    // connect(mainwindow, &MainWindow::shapeChanged, this, &AppDriver::onShapeChanged);
    // connect(mainwindow, &MainWindow::shapeDeleted, this, &AppDriver::onShapeDeleted);
    // connect(mainwindow, &MainWindow::deleteAllShapes, this, &AppDriver::onDeleteAllShapes);
    //for rendered shapes
    connect(renderArea, &RenderArea::shapeAdded, this, &AppDriver::onRenderShapeAdded);
    connect(renderArea, &RenderArea::shapeChanged, this, &AppDriver::onRenderAreaChanged);
    connect(renderArea, &RenderArea::shapeDeleted, this, &AppDriver::onRenderShapeDeleted);
    connect(renderArea, &RenderArea::deleteAllShapes, this, &AppDriver::onRenderDeleteAllShapes);
    //for user accounts
    // connect(loginWindow, &LoginWindow::userAdded, this, &AppDriver::onNewUser);
    // connect(loginWindow, &LoginWindow::userModified, this, &AppDriver::onUserModified);
    // connect(loginWindow, &LoginWindow::userDeleted, this, &AppDriver::onUserDeleted);
    // connect(loginWindow, &LoginWindow::deleteAllUsers, this, &AppDriver::onDeleteAllUsers);
    // connect(loginWindow, &LoginWindow::loginRequested, this, &AppDriver::onLoginAttempt);
}

//Connects the signals in the Manager Classes to the slots in Frontend
void AppDriver::connectManagersToFrontend() {
    //for shapes
    // connect(shapes, &ShapesManager::shapesChanged, mainwindow, &MainWindow::onShapesChanged);
    // connect(shapes, &ShapesManager::shapesNotChanged, mainwindow, &MainWindow::onShapesNotChanged);
    // connect(shapes, &ShapesManager::statusMessage, mainwindow, &MainWindow::showStatusMessage);
    //for rendered shapes
    connect(renderedShapes, &RenderAreaManager::renderAreaChanged, renderArea, &RenderArea::onRenderAreaChanged);
    connect(renderedShapes, &RenderAreaManager::renderAreaNotChanged, renderArea, &RenderArea::onRenderAreaNotChanged);
    connect(renderedShapes, &RenderAreaManager::statusMessage, renderArea, &RenderArea::showStatusMessage);
    //for user accounts
    // connect(user, &UserManager::userChanged, loginWindow, &LoginWindow::onUsersChanged);
    // connect(user, &UserManager::userNotChanged, loginWindow, &LoginWindow::showStatusMessage);
    // connect(user, &UserManager::userAuthenticated, loginWindow, &LoginWindow::onAuthenticated);
    // connect(user, &UserManager::authenticationFailed, loginWindow, &LoginWindow::showStatusMessage);
    // connect(user, &UserManager::statusMessage, loginWindow, &LoginWindow::showStatusMessage);
}