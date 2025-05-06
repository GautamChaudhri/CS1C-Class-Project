// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <algorithm>
#include <QTabWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QFile>
#include <QTimer>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QAction>
#include <QMenuBar>
#include "ui_mainwindow.h"
#include "renderarea.h"
#include "loginwindow.h"
#include "TestimonialDialog.h"
#include "TestimonialsDisplayDialog.h"
#include "ColumnEditDelegate.h"
#include "../backend/UserAccount.h"
#include "../backend/TestimonialManager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The main window of the 2D Graphics Modeler application.
 * @details This class serves as the primary user interface, managing shape rendering,
 *          user interactions, login, testimonials, and displaying shape information.
 *          It coordinates between the UI elements and backend logic.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructors and Destructor.
     * @details These methods handle the creation, initialization, and cleanup
     *          of the MainWindow object.
     */
    explicit MainWindow(QWidget *parent = nullptr);                                 /** @brief Default constructor. */
    MainWindow(QWidget *parent,                                                     /** @brief Constructor initializing with shapes and user data. */
               const alpha::vector<Shape*>* renderedShapes, 
               const UserAccount* currUser); 
    ~MainWindow();                                                                  /** @brief Destructor. Cleans up UI elements and other resources. */

    /**
     * @brief Public interface methods for shape display.
     * @details These methods are responsible for drawing shapes on the render area
     *          and populating the tree widget with shape information.
     */
    void drawShapes() const;                                                        /** @brief Instructs the render area to draw the current shapes. (Note: Actual drawing is typically triggered by `renderArea->update()`). */
    void shapes_to_treeWidget();                                                    /** @brief Populates the tree widget with details of the current shapes and sets up editing controls. */

signals:
    /**
     * @brief Signals related to shape manipulation.
     * @details These signals are emitted to notify other components (likely AppDriver or RenderAreaManager)
     *          about actions performed on shapes by the user through the UI.
     */
    void shapeAdded(Shape* shape);                                                  /** @brief Emitted when a new shape is added by the user. */
    void shapeChanged(Shape* shape, QString key, int value);                        /** @brief Emitted when a property of an existing shape is changed. */
    void displayedTextChanged(Text* text, QString newText);                         /** @brief Emitted when the displayed text of a Text shape is changed. */
    void shapeDeleted(int trackerId);                                               /** @brief Emitted when a shape is requested to be deleted. */
    void deleteAllShapes();                                                         /** @brief Emitted when a request to delete all shapes is made. */

    /**
     * @brief Signals related to user login and signup.
     * @details These signals are emitted to the AppDriver or UserManager to handle
     *          user authentication and account creation processes.
     */
    void loginAttempt(const QString &username, const QString &password);            /** @brief Emitted when a user attempts to log in. */
    void newUserAdded(const QString &username, const QString &password,             /** @brief Emitted when a new user account is requested to be created. */
                                                     const bool admin); 

    /**
     * @brief Signals for controlling dialog flow.
     * @details These signals are used to communicate the success or failure of operations
     *          like login, often to control the state of dialog windows.
     */
    void loginSuccess();                                                            /** @brief Emitted when a login attempt is successful. */
    void loginFailed(const QString &message);                                       /** @brief Emitted when a login attempt fails, providing an error message. */

public slots:
    /**
     * @brief Slots for handling responses from RenderAreaManager.
     * @details These slots are connected to signals from the RenderAreaManager to update
     *          the UI when the state of rendered shapes changes or status messages are available.
     */
    void onRenderAreaChanged();                                                     /** @brief Slot triggered when the render area's content has changed, requiring a UI update. */
    void onRenderAreaNotChanged(const QString& message);                            /** @brief Slot triggered when an operation on the render area did not result in a change (e.g., error). */
    void showRenderStatusMessage(const QString &message);                           /** @brief Displays a status message related to rendering operations. */

    /**
     * @brief Slots for managing the login process.
     * @details These slots handle user interactions related to logging in and signing up.
     */
    void onLoginClicked();                                                          /** @brief Slot triggered when the login button is clicked, typically opening a login dialog. */
    void onLoginRequest(const QString &username, const QString &password);          /** @brief Slot triggered by a login dialog to initiate a login attempt. */
    void onSignupRequest(const QString &username, const QString &password,          /** @brief Slot triggered by a login/signup dialog to initiate account creation. */
                                                        const bool admin); 

    /**
     * @brief Slots for handling responses from UserManager.
     * @details These slots are connected to signals from the UserManager to update the UI
     *          based on the outcome of user authentication attempts.
     */
    void onUserAuthentication(const UserAccount* currUser);                         /** @brief Slot triggered upon successful user authentication. Updates UI with user info. */
    void onUserAuthenticationFailure(const QString& message);                       /** @brief Slot triggered when user authentication fails. Displays an error message. */

private slots:
    /**
     * @brief Slot for UI style toggling.
     * @details This slot handles changes to the application's visual style.
     */
    void onToggleStyle(bool checked = true);                                        /** @brief Toggles the application's stylesheet between predefined styles. */

    /**
     * @brief Slots for shape creation actions.
     * @details These slots are connected to toolbar buttons or menu actions that allow
     *          the user to add new shapes to the canvas.
     */
    void on_actionnew_line_button_triggered();                                      /** @brief Slot triggered to create and add a new Line shape. */
    void on_actionnew_square_button_triggered();                                    /** @brief Slot triggered to create and add a new Square shape. */
    void on_actionnew_rectange_button_triggered();                                  /** @brief Slot triggered to create and add a new Rectangle shape. */
    void on_actionnew_circle_button_triggered();                                    /** @brief Slot triggered to create and add a new Circle shape. */
    void on_actionnew_ellipse_button_triggered();                                   /** @brief Slot triggered to create and add a new Ellipse shape. */
    void on_actionnew_polyline_button_triggered();                                  /** @brief Slot triggered to create and add a new Polyline shape. */
    void on_actionnew_polygon_button_triggered();                                   /** @brief Slot triggered to create and add a new Polygon shape. */
    void on_actionnew_text_button_triggered();                                      /** @brief Slot triggered to create and add a new Text shape. */
    void on_actionremove_shape_button_triggered();                                  /** @brief Slot triggered to remove the currently selected shape. */

    /**
     * @brief Slots for shape sorting functionality in the shape report.
     * @details This slot handles changes in the sorting criteria for the shape table.
     */
    void onSortMethodChanged(int index);                                            /** @brief Slot triggered when the sort method or order in the shape report table changes. */
    
    /**
     * @brief Slots for modifying shape properties via the tree widget.
     * @details These slots respond to user edits made in the shape properties tree,
     *          updating the corresponding shape attributes.
     */
    void onTreeWidgetItemChanged(QTreeWidgetItem* item, int column);                /** @brief Slot triggered when an item in the shape properties tree widget is changed. */
    void onComboBoxChanged(int newIndex);                                           /** @brief Slot triggered when a QComboBox value in the tree widget changes. */
    void onSpinBoxChanged();                                                        /** @brief Slot triggered when a QSpinBox value in the tree widget changes. */

    /**
     * @brief Slots for testimonial UI.
     * @details These slots handle the display of testimonial prompts and the testimonial viewing dialog.
     */
    void showTestimonialPrompt();                                                   /** @brief Displays a dialog prompting the user to submit a testimonial. */
    void showTestimonialsDisplay();                                                 /** @brief Displays a dialog showing existing testimonials. */

    /**
     * @brief Slot for displaying the "Contact Us" window.
     * @details This slot is triggered by a menu action to show contact information.
     */
    void onContactUsClicked();                                                      /** @brief Slot triggered to display the 'Contact Us' information window. */

private:
    /**
     * @brief Core UI components and data pointers.
     * @details These members are essential for the MainWindow's operation, including
     *          the UI definition, rendering area, and pointers to shared data.
     */
    Ui::MainWindow *ui;                                                             /**< @brief Pointer to the auto-generated UI class. */
    RenderArea *renderArea;                                                         /**< @brief Pointer to the custom widget responsible for drawing shapes. */
    const alpha::vector<Shape*>* renderShapes;                                      /**< @brief Pointer to the vector of shapes currently being rendered. */
    const UserAccount* currUser;                                                    /**< @brief Pointer to the currently logged-in user account. */
    QLabel *userStatusLabel;                                                        /**< @brief Label in the status bar to display the current user's login status. */
    ColumnEditDelegate* delegate;                                                   /**< @brief Custom delegate for editing items in the shape properties tree widget. */

    /**
     * @brief Private helper methods for UI management.
     * @details These methods assist in managing UI elements, such as adding shapes
     *          to the tree widget and loading stylesheets.
     */
    void addToShapeTree(Shape* shape);                                              /** @brief Adds a given shape to the properties tree widget and emits shapeAdded signal. */
    QString loadStyleSheet(const QString &path);                                    /** @brief Loads a Qt stylesheet from the specified file path. */

    /**
     * @brief Factory methods for creating QComboBox and QSpinBox widgets.
     * @details These methods are used to dynamically create and configure editor widgets
     *          (like QComboBoxes for color, style, etc., and QSpinBoxes for numerical values)
     *          for the shape properties tree. Each method initializes the widget with items
     *          and sets its current value based on the shape's property.
     */
    QComboBox* createShapeTypeComboBox(const QString& currentShapeType);            /** @brief Creates and configures a QComboBox for selecting shape types. */
    QSpinBox*  createPenWidthSpinBox(int currentPenWidth);                          /** @brief Creates and configures a QSpinBox for editing pen width. */
    QComboBox* createColorComboBox(int currentColor);                               /** @brief Creates and configures a QComboBox for selecting colors. */
    QComboBox* createPenStyleComboBox(int currentPenStyle);                         /** @brief Creates and configures a QComboBox for selecting pen styles. */
    QComboBox* createPenCapStyleComboBox(int currentPenCapStyle);                   /** @brief Creates and configures a QComboBox for selecting pen cap styles. */
    QComboBox* createPenJoinStyleComboBox(int currentPenJoinStyle);                 /** @brief Creates and configures a QComboBox for selecting pen join styles. */
    QComboBox* createBrushStyleComboBox(int currentBrushStyle);                     /** @brief Creates and configures a QComboBox for selecting brush styles. */
    QComboBox* createAlignmentComboBox(Qt::AlignmentFlag currentAlignment);         /** @brief Creates and configures a QComboBox for selecting text alignment. */
    QComboBox* createFontComboBox(QFont currentFont);                               /** @brief Creates and configures a QComboBox for selecting font families. */
    QComboBox* createFontStyleComboBox(int currentFontStyle);                       /** @brief Creates and configures a QComboBox for selecting font styles (normal, italic, oblique). */
    QComboBox* createFontWeightComboBox(QFont::Weight currentFontWeight);           /** @brief Creates and configures a QComboBox for selecting font weights. */

    /**
     * @brief Methods and members related to the shape report table.
     * @details These are used to create, populate, and manage the tab/window
     *          that displays a sortable table of shape properties.
     */
    void createShapeTableTab();                                                     /** @brief Creates and displays a new tab or window containing the shape report table. */
    QTabWidget* tabWidget;                                                          /**< @brief Pointer to the tab widget (if used for the shape report, otherwise could be for other purposes). */
    QTableWidget* shapeTable;                                                       /**< @brief Pointer to the table widget used to display shape properties in the report. */
    QComboBox* sortDropdown;                                                        /**< @brief Dropdown QComboBox for selecting the sorting criterion in the shape report. */
    QComboBox* sortOrderDropdown;                                                   /**< @brief Dropdown QComboBox for selecting the sorting order (ascending/descending) in the shape report. */

    /**
     * @brief Sorting algorithm and comparison functions for the shape report.
     * @details Implements a selection sort algorithm and provides static comparison
     *          functions used to sort shapes by different criteria.
     */
    void selection_sort(alpha::vector<Shape*>& shapes,                              /** @brief Implements the selection sort algorithm for a vector of shapes. */
                        bool (*compare)(const Shape*, const Shape*), 
                        bool ascending); 
    void populateShapeTable(const alpha::vector<Shape*>& shapes);                   /** @brief Populates the shape report table with data from the provided vector of shapes. */
    static bool sortById(const Shape* a, const Shape* b);                           /** @brief Static comparison function to sort shapes by their ID. */
    static bool sortByArea(const Shape* a, const Shape* b);                         /** @brief Static comparison function to sort shapes by their calculated area. */
    static bool sortByPerimeter(const Shape* a, const Shape* b);                    /** @brief Static comparison function to sort shapes by their calculated perimeter. */
    
    /**
     * @brief Testimonial feature setup.
     * @details This method initializes components related to the testimonial feature.
     */
    void setupTestimonials();                                                       /** @brief Sets up connections and UI elements for the testimonial feature. */

    /**
     * @brief Members for the "Contact Us" window.
     * @details Pointers to widgets used in the "Contact Us" information display.
     */
    QWidget *contactUsWidget;                                                       /**< @brief Pointer to the main widget for the Contact Us display. */
    QLabel *logoLabel;                                                              /**< @brief Label to display the team logo in the Contact Us display. */
    QLabel *teamNameLabel;                                                          /**< @brief Label to display the team name in the Contact Us display. */
    QWidget *contactWindow;                                                         /**< @brief Pointer to the QWidget that serves as the 'Contact Us' window. */
};

#endif // MAINWINDOW_H
