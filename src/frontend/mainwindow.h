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
namespace Ui{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void drawShapes() const;

    void shapes_to_treeWidget();

public slots:
    void setShapes(const alpha::vector<Shape*>& shapes);

private slots:
    void on_actionnew_shape_button_triggered();

private:
    Ui::MainWindow *ui;
    RenderArea *renderArea;
};
#endif // MAINWINDOW_H
