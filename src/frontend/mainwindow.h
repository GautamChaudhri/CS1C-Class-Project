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

    RenderArea* getRenderAreaRef();
    void drawShapes() const;

    void shapes_to_treeWidget();

public slots:
    void setShapes(const alpha::vector<Shape*>& shapes);

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
