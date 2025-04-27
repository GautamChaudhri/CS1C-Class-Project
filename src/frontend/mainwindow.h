// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QWidget *parent,
               const alpha::vector<Shape*>* renderedShapes,
               const UserAccount* currUser);
    ~MainWindow();

    RenderArea* getRenderAreaRef();
    void drawShapes() const;
    void shapes_to_treeWidget();

signals:
    // shape signals
    void shapeAdded(Shape* shape);
    void shapeChanged(Shape* shape);
    void shapeDeleted(int trackerId);
    void deleteAllShapes();

    // login/signup signals into AppDriver
    void loginAttempt(const QString &username, const QString &password);
    void newUserAdded(const QString &username, const QString &password, const bool admin);

    // dialog-control signals
    void loginSuccess();
    void loginFailed(const QString &message);

public slots:
    // shape slots...
    void onShapesChanged();
    void onShapesNotChanged(const QString& message);
    void showShapesStatusMessage(const QString &message);
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

private:
    Ui::MainWindow *ui;
    RenderArea *renderArea;
    const alpha::vector<Shape*>* renderShapes;
    const UserAccount* currUser;
    QLabel *userStatusLabel;

    void addToShapeTree(Shape* shape);

    QString loadStyleSheet(const QString &path);

    QComboBox* createShapeTypeComboBox(const QString& currentShapeType);
    QComboBox* createPenStyleComboBox(int currentPenStyle);
    QComboBox* createBrushStyleComboBox(int currentBrushStyle);
};

#endif // MAINWINDOW_H