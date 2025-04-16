#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , renderArea(new RenderArea(this))
{
    ui->setupUi(this);

    //Sets the render area on the screen
    renderArea.setGeometry(50, 105, 1000, 850);

    //Ensures the widget doesn't block the buttons in the main window
    renderArea.setAttribute(Qt::WA_TransparentForMouseEvents);
}

void MainWindow::setShapes(const alpha::vector<Shape*>& shapes) {
    // store the shapes, trigger re-render, etc.
}


MainWindow::~MainWindow()
{  
    delete ui;
}

