#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "renderarea.h"
#include "../backend/Parser.h"
#include "../backend/ApiClient.h"
#include <QApplication>
#include <QGridLayout>
#include "ui_mainwindow.h"
#include "../backend/UserAccount.h"

QT_BEGIN_NAMESPACE
namespace Ui{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QWidget *parent, const alpha::vector<Shape*>* shapes,
               const alpha::vector<Shape*>* renderedShapes, const UserAccount* currUser);
    ~MainWindow();

    void setShapes2(const alpha::vector<Shape*>& shapes);

    RenderArea* getRenderAreaRef();
    void drawShapes() const;

    void shapes_to_treeWidget();

signals:
    // These signals connect to the slots in the AppDriver class
    void shapeAdded(Shape* shape);
    void shapeChanged(Shape* shape);
    void shapeDeleted(int trackerId);
    void deleteAllShapes();

public slots:
    void setShapes(const alpha::vector<Shape*>& shapes);

    // Signals for these slots come from RenderAreaManager class
    void onRenderAreaChanged();
    void onRenderAreaNotChanged(const QString& message);
    void showStatusMessage(QString msg);

private slots:
    void on_actionnew_shape_button_triggered();

private:
    Ui::MainWindow *ui;
    RenderArea *renderArea;

    const alpha::vector<Shape*>* shapes;
    const alpha::vector<Shape*>* renderedShapes;
    const UserAccount* currUser;
};
#endif // MAINWINDOW_H
