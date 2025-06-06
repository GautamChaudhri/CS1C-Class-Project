#include "AppDriver.h"

AppDriver::AppDriver(QObject* parent) 
          : QObject{parent}, renderedShapes{new RenderAreaManager}, 
            user{new UserManager} {}

AppDriver::~AppDriver() {
    delete renderedShapes;
    delete user;
}

void AppDriver::run() {
    // Construct the main window and grab its renderArea
    mainWindow = new MainWindow(nullptr,
                    renderedShapes->getShapesRef(),
                    user->getCurrUserRef());

    // Connect signals BEFORE loading data
    connectFrontendToDriver();
    connectManagersToFrontend();

    // Finally show the window
    mainWindow->show();

    // Defer loading until after the event loop starts
    qDebug() << "[AppDriver:run] initializing main window";
    QTimer::singleShot(0, this, [this]() {
        loadAllData();
    });
}

void AppDriver::shutdown() {
    qDebug() << "[AppDriver:shutdown] saving shapes and users";
    renderedShapes->saveShapes();
    user->saveUsers();
}

void AppDriver::loadAllData() {
    qDebug() << "[AppDriver:loadAllData] loading shapes and users";
    renderedShapes->loadShapes();
    user->loadUsers();
}

//=========================================== SLOTS ===================================================

void AppDriver::onRenderShapeAdded(Shape* shape) {
    renderedShapes->addShape(shape);
}

void AppDriver::onRenderShapeChanged(Shape* shape, QString key, int value) {
    renderedShapes->modifyShape(shape, key, value);
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

void AppDriver::connectFrontendToDriver() {
    //for rendered shapes
    connect(mainWindow, &MainWindow::shapeAdded, this, &AppDriver::onRenderShapeAdded);
    connect(mainWindow, &MainWindow::shapeChanged, this, &AppDriver::onRenderShapeChanged);
    connect(mainWindow, &MainWindow::shapeDeleted, this, &AppDriver::onRenderShapeDeleted);
    connect(mainWindow, &MainWindow::deleteAllShapes, this, &AppDriver::onRenderDeleteAllShapes);
    connect(mainWindow, &MainWindow::displayedTextChanged, renderedShapes, &RenderAreaManager::modifyDisplayedText);
    //for user accounts
    connect(mainWindow, &MainWindow::newUserAdded, this, &AppDriver::onNewUser);
    // connect(loginWindow, &LoginWindow::userModified, this, &AppDriver::onUserModified);
    // connect(loginWindow, &LoginWindow::userDeleted, this, &AppDriver::onUserDeleted);
    // connect(loginWindow, &LoginWindow::deleteAllUsers, this, &AppDriver::onDeleteAllUsers);
    connect(mainWindow, &MainWindow::loginAttempt, this, &AppDriver::onLoginAttempt);
}

void AppDriver::connectManagersToFrontend() {
    qDebug() << "AppDriver::connectManagersToFrontend() – hooking up shapesChanged → onShapesChanged";
    //for rendered shapes
    connect(renderedShapes, &RenderAreaManager::renderAreaChanged, mainWindow, &MainWindow::onRenderAreaChanged);
    connect(renderedShapes, &RenderAreaManager::renderAreaNotChanged, mainWindow, &MainWindow::onRenderAreaNotChanged);
    connect(renderedShapes, &RenderAreaManager::statusMessage, mainWindow, &MainWindow::showRenderStatusMessage);
    //for user accounts
    connect(user, &UserManager::userAuthenticated, mainWindow, &MainWindow::onUserAuthentication);
    connect(user, &UserManager::authenticationFailed, mainWindow, &MainWindow::onUserAuthenticationFailure);
    // connect(user, &UserManager::statusMessage, loginWindow, &LoginWindow::showStatusMessage);
}
