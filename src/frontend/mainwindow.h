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
#include <QComboBox>
#include <QStatusBar>
#include "ui_mainwindow.h"
#include "renderarea.h"
#include "loginwindow.h"
#include "../backend/UserAccount.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    MainWindow(QWidget *parent, const alpha::vector<Shape*>* renderedShapes, const UserAccount* currUser);
    ~MainWindow();

    void drawShapes() const;
    void shapes_to_treeWidget();

signals:
    // shape signals
    void shapeAdded(Shape* shape);
    void shapeChanged(Shape* shape, QString key, int vaue);
    void displayedTextChanged(Text* text, QString newText);
    void shapeDeleted(int trackerId);
    void deleteAllShapes();

    // login/signup signals into AppDriver
    void loginAttempt(const QString &username, const QString &password);
    void newUserAdded(const QString &username, const QString &password, const bool admin);

    // dialog-control signals
    void loginSuccess();
    void loginFailed(const QString &message);

public slots:
    // Signals for these slots come from RenderAreaManager class
    void onRenderAreaChanged();
    void onRenderAreaNotChanged(const QString& message);
    void showRenderStatusMessage(const QString &message);

    // login flow
    void onLoginClicked();
    void onLoginRequest(const QString &username, const QString &password);
    void onSignupRequest(const QString &username, const QString &password, const bool admin);

    // responses from UserManager
    void onUserAuthentication(const UserAccount* currUser);
    void onUserAuthenticationFailure(const QString& message);

private slots:

    void onToggleStyle(bool checked = true);

    void on_actionnew_line_button_triggered();
    void on_actionnew_square_button_triggered();
    void on_actionnew_rectange_button_triggered();
    void on_actionnew_circle_button_triggered();
    void on_actionnew_ellipse_button_triggered();
    void on_actionnew_polyline_button_triggered();
    void on_actionnew_polygon_button_triggered();
    void on_actionnew_text_button_triggered();
    void on_actionremove_shape_button_triggered();

    // For Selection Sort Algo
    void onSortMethodChanged(int index);
    
    // For modifying shape
    void onTreeWidgetItemChanged(QTreeWidgetItem*, int column);
    void onComboBoxChanged(int newIndex);

    void showTestimonialPrompt();
    void showTestimonialsDisplay();

private:
    Ui::MainWindow *ui;
    RenderArea *renderArea;

    const alpha::vector<Shape*>* renderShapes;      // Holds currently renderedShapes
    const UserAccount* currUser;
    QLabel *userStatusLabel;

    void addToShapeTree(Shape* shape);

    QString loadStyleSheet(const QString &path);

    QComboBox* createShapeTypeComboBox(const QString& currentShapeType);

    QComboBox* createPenColorComboBox(int currentPenColor);
    QComboBox* createPenStyleComboBox(int currentPenStyle);
    QComboBox* createPenCapStyleComboBox(int currentPenCapStyle);
    QComboBox* createPenJoinStyleComboBox(int currentPenJoinStyle);

    QComboBox* createBrushStyleComboBox(int currentBrushStyle);

    QComboBox* createAlignmentComboBox(AlignmentFlag currentAlignment);
    QComboBox* createFontComboBox(QFont currentFont);
    QComboBox* createFontStyleComboBox(int currentFontStyle);
    QComboBox* createFontWeightComboBox(QFont::Weight currentFontWeight);

    void createShapeTableTab();
    QTabWidget* tabWidget; // Tab widget to manage tabs
    QTableWidget* shapeTable; // Table to display shapes
    QComboBox* sortDropdown; // Dropdown for sorting methods
    QComboBox* sortOrderDropdown; // Dropdown for sorting order

    void selection_sort(alpha::vector<Shape*>& shapes, bool (*compare)(const Shape*, const Shape*), bool ascending);

    void populateShapeTable(const alpha::vector<Shape*>& shapes);

    static bool sortById(const Shape* a, const Shape* b);
    static bool sortByArea(const Shape* a, const Shape* b);
    static bool sortByPerimeter(const Shape* a, const Shape* b);
    
    void setupTestimonials();

};

#endif // MAINWINDOW_H
