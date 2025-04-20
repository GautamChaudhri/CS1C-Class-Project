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

    QTreeWidgetItem* temp = new QTreeWidgetItem();
    temp->setText(0, "temp");

    // ui->treeWidget->addTopLevelItem(temp);
    // Line* line = new Line(1, "Line", QPoint(500, 500), QPen(), QBrush(), QPoint(500,500), QPoint(700, 700));
    // ui->treeWidget->addTopLevelItem(line->getParentItem());
    //qDebug() << "Shape count: " << renderArea->getShapes().size();


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
}

void MainWindow::shapes_to_treeWidget()
{
    qDebug() << "Shape count: " << renderArea->getShapes().size();
    for (int i = 0; i < renderArea->getShapes().size(); ++i)
    {
        qDebug() << "Shape count: " << renderArea->getShapes().size();
        ui->treeWidget->addTopLevelItem(renderArea->getShapes()[i]->getParentItem());
    }
}
