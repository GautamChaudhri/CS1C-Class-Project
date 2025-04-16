#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    renderArea = new RenderArea(this);

    //Sets the render area on the screen
    renderArea->setGeometry(50, 105, 1000, 850);

    //Ensures the widget doesn't block the buttons in the main window
    renderArea->setAttribute(Qt::WA_TransparentForMouseEvents);
}


MainWindow::~MainWindow()
{  
    delete ui;
}

void MainWindow::setShapes(const alpha::vector<Shape*>& shapes) {
    //updates the shape vector in renderArea and then draws it again
    renderArea->setShapes(shapes);
    renderArea->update();
}

