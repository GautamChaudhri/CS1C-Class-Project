#include "mainwindow.h"
#include "renderarea.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    RenderArea *customWidget = new RenderArea(this);
    customWidget->setGeometry(0, 0, width(), height());
}

MainWindow::~MainWindow()
{  
    delete ui;
}

