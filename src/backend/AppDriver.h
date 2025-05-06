#ifndef APP_DRIVER_H
#define APP_DRIVER_H
#include <QCoreApplication>
#include <QApplication>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include "RenderAreaManager.h"
#include "UserManager.h"
#include "../frontend/mainwindow.h"
#include "../frontend/renderarea.h"

/**
 * @brief Orchestrates the main application logic and connections.
 *
 * The AppDriver class is responsible for initializing and managing the main components
 * of the application, including the RenderAreaManager, UserManager, and the MainWindow.
 * It handles the setup of signal-slot connections between the frontend UI elements
 * and the backend data managers. It also manages the application lifecycle,
 * including startup, data loading, and shutdown procedures.
 */
class AppDriver : public QObject {
    Q_OBJECT
public:
    /**
     * @name Core Application Lifecycle
     * @brief Public interface for the AppDriver.
     * @details This section includes the constructor, destructor, and core methods
     *          for running, shutting down, and loading data for the application.
     */
    /** @{ */
    AppDriver(QObject* parent = nullptr);                   ///< Constructs the AppDriver and initializes manager objects.
    ~AppDriver();                                           ///< Destroys the AppDriver and cleans up manager objects.
    void run();                                             ///< Initializes and shows the main application window and loads initial data.
    void shutdown();                                        ///< Saves data from managers before the application closes.
    void loadAllData();                                     ///< Triggers the loading of all necessary data by the managers.
    /** @} */


private slots:
    /**
     * @name Render Area UI Slots
     * @brief Slots connecting the render area UI to RenderAreaManager data.
     * @details These slots handle signals from the frontend render area, such as
     *          shape additions, modifications, and deletions, and delegate these
     *          actions to the RenderAreaManager.
     */
    /** @{ */
    void onRenderShapeAdded(Shape* shape);                  ///< Handles the addition of a new shape from the render area.
    void onRenderShapeChanged(Shape* shape,                 ///< Handles modifications to an existing shape from the render area.
                              QString key, 
                              int value);                   
    void onRenderShapeDeleted(const int trackerId);         ///< Handles the deletion of a single shape from the render area.
    void onRenderDeleteAllShapes();                         ///< Handles the request to delete all shapes from the render area.
    /** @} */

    /**
     * @name User Management UI Slots
     * @brief Slots connecting the user login UI to UserManager data.
     * @details These slots handle signals related to user management from the
     *          frontend, such as new user creation, credential modification,
     *          user deletion, and login attempts, delegating these actions
     *          to the UserManager.
     */
    /** @{ */
    void onNewUser(const QString username,                  ///< Handles the creation of a new user.
                   const QString password, 
                   const bool admin);                       
    void onUserModified(const QString username,             ///< Handles modification of an existing user's credentials.
                        const QString password, 
                        const bool admin);                  
    void onUserDeleted(const QString username);             ///< Handles the deletion of a single user.
    void onDeleteAllUsers();                                ///< Handles the request to delete all users.
    void onLoginAttempt(const QString username,             ///< Handles a user login attempt.
                        const QString password);            
    /** @} */


private:
    /**
     * @name Core Components
     * @brief Private member variables for the AppDriver.
     * @details These members hold pointers to the core manager classes and the main window.
     */
    /** @{ */
    MainWindow* mainWindow;                                 ///< Pointer to the main application window.
    RenderAreaManager* renderedShapes;                      ///< Manages all the shapes that are currently rendered.
    UserManager* user;                                      ///< Manages the current user and holds all existing users to authenticate against.
    /** @} */
    

    /**
     * @name Connection Setup Helpers
     * @brief Private helper methods for setting up connections.
     * @details These subroutines are called during initialization to establish
     *          signal-slot connections between different components of the application.
     */
    /** @{ */
    void connectFrontendToDriver();                         ///< Connects signals from the frontend UI to slots in this AppDriver.
    void connectManagersToFrontend();                       ///< Connects signals from backend managers to slots in the frontend UI.
    /** @} */
};

#endif // APP_DRIVER_H
