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
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(renderArea);
}

MainWindow::MainWindow(QWidget *parent = nullptr, const alpha::vector<Shape*>* shapes,
    const alpha::vector<Shape*>* renderedShapes, const UserAccount* currUser)
    : QMainWindow(parent), 
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Manually create the RenderArea and insert it into the placeholder container
    renderArea = new RenderArea(ui->renderAreaContainer);

    // Create a layout to manage the RenderArea inside the container
    auto layout = new QVBoxLayout(ui->renderAreaContainer);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(renderArea);

    renderArea->setShapes(renderedShapes);
}


MainWindow::~MainWindow()
{  
    delete ui;
    delete renderArea;
}

void MainWindow::setShapes(const alpha::vector<Shape*>& shapes) {
    //updates the shape vector in renderArea and then draws it again
    renderArea->setShapes(shapes);
    renderArea->update();
}


void MainWindow::on_actionnew_shape_button_triggered()
{
    Line* line = new Line(1, "Line", QPoint(500, 500), QPen(), QBrush(), QPoint(500, 500), QPoint(700, 700));

    renderArea->addShape(line);
    renderArea->update();
    shapes_to_treeWidget(); // add new shape to tree widget as it is created
}

void MainWindow::shapes_to_treeWidget()
{
    int vecSize;
    vecSize = renderArea->getShapes().size();

    for (int i = 0; i < vecSize; ++i)
    {
        ui->treeWidget->addTopLevelItem(renderArea->getShapes()[i]->getParentItem());
    }
}

RenderArea* MainWindow::getRenderAreaRef() {
    return renderArea;
}