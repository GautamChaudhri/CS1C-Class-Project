#include "mainwindow.h"
#include "renderarea.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Creates custom widget
    RenderArea *customWidget = new RenderArea(this);

    //Sets the render area on the screen
    customWidget->setGeometry(50, 105, 1000, 850);

    //Ensures the widget doesn't block the buttons in the main window
    customWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
}

MainWindow::~MainWindow()
{  
    delete ui;
}

