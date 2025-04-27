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

    // Store references for data
    this->allShapes = shapes;
    this->renderShapes = renderedShapes;
    this->currUser = currUser;

    // Set render shapes AFTER renderArea is fully initialized
    renderArea->setRenderShapes(renderedShapes);

    // Connect the toggleStyle signal to its slot
    connect(ui->toggleStyle, &QAction::toggled, this, &MainWindow::onToggleStyle);
    onToggleStyle(ui->toggleStyle->isChecked());
}



MainWindow::~MainWindow()
{  
    delete ui;
    delete renderArea;
}

void MainWindow::shapes_to_treeWidget()
{
    Shape* item;
    int vecSize;

    item = nullptr;
    vecSize = renderArea->getShapes().size();

    for (int i = 0; i < vecSize; ++i)
    {
        item = renderArea->getShapes()[i];

        // Creates the objects to hold the combo boxes
        QComboBox* penStyleCombo = createPenStyleComboBox(item->getPenStyle());
        QComboBox* brushStyleCombo = createBrushStyleComboBox(item->getBrushStyle());

        // Set parent of combo box as treeWidget
        penStyleCombo->setParent(ui->treeWidget);
        brushStyleCombo->setParent(ui->treeWidget);

        // Add top-level item to the tree widget
        ui->treeWidget->addTopLevelItem(item->getParentItem());

        // Add the comboboxes to the children
        // switch (item->getShapeId())
        // {
        // case 1:
        //     ui->treeWidget->setItemWidget(item->getChildItems()[5], 1, penStyleCombo);
        //     ui->treeWidget->setItemWidget(item->getChildItems()[6], 1, brushStyleCombo);
        //     break;

        // case 2:
        //     ui->treeWidget->setItemWidget(item->getChildItems()[5], 1, penStyleCombo);
        //     ui->treeWidget->setItemWidget(item->getChildItems()[6], 1, brushStyleCombo);
        //     break;
        // }

        item->getParentItem()->setText(0, QString::fromStdString(item->getShapeType()));

        for (int i = 0; i < 7; ++i) // 6 being # of data members in shape being displayed for all shapes (JUST FOR TESTING PLEASE CHANGE)
        {
            item->getChildItems().push_back(new QTreeWidgetItem());
            item->getParentItem()->addChild(item->getChildItems()[i]);
        }
        // hard coded spaces for each subitem, change as you please
        item->getChildItems()[0]->setText(0, "Shape ID:");
        item->getChildItems()[0]->setText(1, QString::number(item->getShapeId()));

        item->getChildItems()[1]->setText(0, "Tracker ID:");
        item->getChildItems()[1]->setText(1, QString::number(item->getTrackerId()));

        item->getChildItems()[2]->setText(0, "Shape Type:");
        item->getChildItems()[2]->setText(1, QString::fromStdString(item->getShapeType()));

        item->getChildItems()[3]->setText(0, "X:");
        item->getChildItems()[3]->setText(1, QString::number(item->getX()));
        item->getChildItems()[3]->setFlags(item->getChildItems()[3]->flags() | Qt::ItemIsEditable);

        item->getChildItems()[4]->setText(0, "Y:");
        item->getChildItems()[4]->setText(1, QString::number(item->getY()));
        item->getChildItems()[4]->setFlags(item->getChildItems()[4]->flags() | Qt::ItemIsEditable);

    }
}

RenderArea* MainWindow::getRenderAreaRef() {
    return renderArea;
}

void MainWindow::onShapesChanged() {
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
    shapes_to_treeWidget();
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
    emit shapeAdded(shape);
    renderArea->update();
    shapes_to_treeWidget(); // add new shape to tree widget as it is created
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
    QString path = checked
                       ? ":styles/Geoo.qss"
                       : ":styles/Medize.qss";

    QString style = loadStyleSheet(path);
    // qDebug() << "Applying style:" << path;
    // qDebug() << "Style size:" << style.length(); // Should be > 0

    qApp->setStyleSheet(style);
}

QComboBox* MainWindow::createPenStyleComboBox(int currentPenStyle)
{
    QComboBox* box = new QComboBox();
    box->addItem("NoPen", static_cast<int>(Qt::NoPen));
    box->addItem("SolidLine", static_cast<int>(Qt::SolidLine));
    box->addItem("DashLine", static_cast<int>(Qt::DashLine));
    box->addItem("DotLine", static_cast<int>(Qt::DotLine));
    box->addItem("DashDotLine", static_cast<int>(Qt::DashDotLine));
    box->addItem("DashDotDotLine", static_cast<int>(Qt::DashDotDotLine));
    box->setCurrentIndex(currentPenStyle);
    return box;
}

QComboBox* MainWindow::createBrushStyleComboBox(int currentBrushStyle)
{
    QComboBox* box = new QComboBox();
    box->addItem("NoBrush", static_cast<int>(Qt::NoBrush));
    box->addItem("SolidPattern", static_cast<int>(Qt::SolidPattern));
    box->addItem("Dense1Pattern", static_cast<int>(Qt::Dense1Pattern));
    box->addItem("Dense2Pattern", static_cast<int>(Qt::Dense2Pattern));
    box->addItem("Dense3Pattern", static_cast<int>(Qt::Dense3Pattern));
    box->addItem("Dense4Pattern", static_cast<int>(Qt::Dense4Pattern));
    box->addItem("Dense5Pattern", static_cast<int>(Qt::Dense5Pattern));
    box->addItem("Dense6Pattern", static_cast<int>(Qt::Dense6Pattern));
    box->addItem("Dense7Pattern", static_cast<int>(Qt::Dense7Pattern));
    box->addItem("HorPattern", static_cast<int>(Qt::HorPattern));
    box->addItem("VerPattern", static_cast<int>(Qt::VerPattern));
    box->addItem("CrossPattern", static_cast<int>(Qt::CrossPattern));
    box->addItem("BDiagPattern", static_cast<int>(Qt::BDiagPattern));
    box->addItem("FDiagPattern", static_cast<int>(Qt::FDiagPattern));
    box->addItem("DiagCrossPattern", static_cast<int>(Qt::DiagCrossPattern));
    box->setCurrentIndex(currentBrushStyle);
    return box;
}


void MainWindow::on_actionremove_shape_button_triggered()
{
    try
    {
        if(renderArea->getShapeSelectedIndex() >= 0)
        {
            qDebug() << "Selected Index: " << renderArea->getShapeSelectedIndex();
            qDebug() << "Tracker ID: "     << renderArea->getShapeSelected();

            emit shapeDeleted(renderArea->getShapeSelected());
        }
    }
    catch (...)
    {
        // The code works but an exception keeps being thrown which is why this exists :/
    }

    renderArea->resetSelection();
}

