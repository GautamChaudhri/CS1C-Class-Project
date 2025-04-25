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

MainWindow::MainWindow(QWidget *parent, const alpha::vector<Shape*>* shapes,
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

    // Set up shape selector box
    shapeSelector = new QComboBox(this);
    ui->toolBar->addWidget(shapeSelector);

    // Store references for data
    this->allShapes = shapes;
    this->renderShapes = renderedShapes;
    this->currUser = currUser;
    renderArea->setShapes(shapes);
    renderArea->setRenderShapes(renderedShapes);
}


MainWindow::~MainWindow()
{  
    delete ui;
    delete renderArea;
}

void MainWindow::setShapes(const alpha::vector<Shape*>& shapes) {
    //updates the shape vector in renderArea and then draws it again
    renderArea->setShapes2(shapes);
    renderArea->update();
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

void MainWindow::onShapesChanged() {
    qDebug() << "onShapesChanged(): allShapes size =" 
             << (allShapes ? allShapes->size() : -1);
    shapeSelector->clear();
    for (Shape* shapeType : *allShapes) {
        QString shapeName = QString::fromStdString(shapeType->getShapeType());
        shapeSelector->addItem(shapeName);
    }
    
}

void MainWindow::onShapesNotChanged(const QString& message) {
    // handle error: you could show a popup or log the message
}

void MainWindow::showShapesStatusMessage(const QString& message)
{
    qDebug() << "Shapes Status:" << message;
}

void MainWindow::onRenderAreaChanged() {
    update();
}

void MainWindow::onRenderAreaNotChanged(const QString& message) {
    // handle error: you could show a popup or log the message
}

void MainWindow::showRenderStatusMessage(const QString &message)
{
    qDebug() << "Status:" << message;
}


void MainWindow::on_actionnew_square_button_triggered()
{
    Square* square = new Square(0, "Square", QPoint(0, 0), QPen(), QBrush(), 100);

    addToShapeTree(square);
}

void MainWindow::on_actionnew_line_button_triggered()
{
    Line* line = new Line(4, "Line", QPoint(0, 0), QPen(), QBrush(), QPoint(0, 0), QPoint(50, 50));

    addToShapeTree(line);
}


void MainWindow::on_actionnew_rectange_button_triggered()
{
    Rectangle* rectangle = new Rectangle(1, "Rectangle", QPoint(0, 0), QPen(), QBrush(), 100, 50);

    addToShapeTree(rectangle);
}


void MainWindow::on_actionnew_circle_button_triggered()
{
    Circle* circle = new Circle(2, "Circle", QPoint(25, 25), QPen(), QBrush(), 25);

    addToShapeTree(circle);
}


void MainWindow::on_actionnew_ellipse_button_triggered()
{
    Ellipse* ellipse = new Ellipse(3, "Ellipse", QPoint(25, 20), QPen(), QBrush(), 25, 20);

    addToShapeTree(ellipse);
}


void MainWindow::on_actionnew_polyline_button_triggered()
{
    Polyline* polyline = new Polyline(5, "Polyline", QPoint(50, 100), QPen(), QBrush(), QPolygon({QPoint(50, 100), QPoint(100, 50), QPoint(150, 100)}));

    addToShapeTree(polyline);
}


void MainWindow::on_actionnew_polygon_button_triggered()
{
    Polygon* polygon = new Polygon(6, "Polygon", QPoint(50, 100), QPen(), QBrush(), QPolygon({QPoint(50, 100), QPoint(100, 50), QPoint(150, 100)}));

    addToShapeTree(polygon);
}


void MainWindow::on_actionnew_text_button_triggered()
{
    Text* text = new Text(7, "Text", QPoint(0, 0), "Hello World", Qt::black, Qt::AlignLeft, QFont("Arial", 12), 100, 50);

    addToShapeTree(text);
}

void MainWindow::addToShapeTree(Shape* shape)
{
    renderArea->addShape(shape);
    renderArea->update();
    shapes_to_treeWidget(); // add new shape to tree widget as it is created
}

