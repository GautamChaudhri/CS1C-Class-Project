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

    connect(ui->toggleStyle, &QAction::toggled, this, &MainWindow::onToggleStyle);
    onToggleStyle(ui->toggleStyle->isChecked());

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

QString MainWindow::loadStyleSheet(const QString &path)
{
    QFile file(path);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Could not open stylesheet:" << path;
        return "";
    }

    QTextStream in(&file);

    return in.readAll();
}

void MainWindow::onToggleStyle(bool checked) {
    if (checked) {
        QString darkStyle = loadStyleSheet(":/qdarkstyle/dark/darkstyle.qss");
        qApp->setStyleSheet(darkStyle);
    } else {
        QString lightStyle = loadStyleSheet(":/qdarkstyle/light/lightstyle.qss");
        qApp->setStyleSheet(lightStyle);
    }
}
