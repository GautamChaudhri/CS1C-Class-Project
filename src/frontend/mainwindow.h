#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "renderarea.h"
#include "Parser.h"
#include "ApiClient.h"
#include <QApplication>
#include <QGridLayout>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(QWidget *parent = nullptr, const alpha::vector<Shape*>* shapes,
             const alpha::vector<Shape*>* renderedShapes, const UserAccount* user);
    ~MainWindow();

    void drawShapes() const;

public slots:
    
    
private slots:
    void onRenderAreaChange();

private:
    Ui::MainWindow *ui;
    RenderArea *renderArea;

    alpha::vector<Shape*>* shapes;
    alpha::vector<Shape*>* renderedShapes;
    UserAccount* user;
};
#endif // MAINWINDOW_H
