#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Manually create the RenderArea and insert it into the placeholder container
    renderArea = new RenderArea(ui->renderAreaContainer);

    // Create a layout to manage the RenderArea inside the container
    auto layout = new QVBoxLayout(ui->renderAreaContainer);
    layout->setContentsMargins(0, 0, 0, 0); // Optional: remove padding
    layout->addWidget(renderArea);

    // This prevents mouse detection which is why it is commented
    //renderArea->setAttribute(Qt::WA_TransparentForMouseEvents);
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

// Create Square - TEST
void MainWindow::on_toolButton_triggered(QAction *arg1)
{
    Square square(5, "Square", QPoint(500, 500), QPen(), QBrush(), 200);

    square.Draw(renderArea);
    renderArea->update();
}

// Create Square - TEST
void MainWindow::on_toolButton_clicked()
{
    Square square(5, "Square", QPoint(500, 500), QPen(), QBrush(), 200);

    square.Draw(renderArea);
    renderArea->update();
}

// Create Square - TEST
void MainWindow::on_toolButton_pressed()
{
    Square square(5, "Square", QPoint(500, 500), QPen(), QBrush(), 200);

    square.Draw(renderArea);
    renderArea->update();
}

