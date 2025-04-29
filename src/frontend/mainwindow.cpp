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

MainWindow::MainWindow(QWidget *parent, const alpha::vector<Shape*>* renderedShapes, const UserAccount* currUser)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // wire up handler for edits in the tree
    connect(ui->treeWidget, &QTreeWidget::itemChanged, this, &MainWindow::onTreeWidgetItemChanged);

    // Manually create the RenderArea and insert it into the placeholder container
    renderArea = new RenderArea(ui->renderAreaContainer);

    // Create a layout to manage the RenderArea inside the container
    auto layout = new QVBoxLayout(ui->renderAreaContainer);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(renderArea);

    // Store references for data
    this->renderShapes = renderedShapes;
    this->currUser = currUser;

    // Set render shapes AFTER renderArea is fully initialized
    renderArea->setRenderShapes(renderedShapes);

    // Connect the toggleStyle signal to its slot
    connect(ui->toggleStyle, &QAction::toggled, this, &MainWindow::onToggleStyle);
    onToggleStyle(ui->toggleStyle->isChecked());
    
    //Login
    userStatusLabel = new QLabel("Logged in as: " + currUser->getUsername(), this);
    statusBar()->addPermanentWidget(userStatusLabel);
    auto *loginButton = new QPushButton("Login", this);
    statusBar()->addPermanentWidget(loginButton);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginClicked);

    // This creates a separate window when clicked
    ui->menuFile->addAction(tr("Open Shape Report"), this, &MainWindow::createShapeTableTab);
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
        item->getParentItem()->setData(0, Qt::UserRole, QVariant::fromValue(item->getTrackerId()));
    }
}

void MainWindow::onTreeWidgetItemChanged(QTreeWidgetItem* item, int column) {
    // Only proceed if changes made occurred in column 1 and in child items
    if (column != 1 || !item->parent()) return;

    QString key = item->text(0);
    bool ok = false;
    int value = item->text(1).toInt(&ok);
    if (!ok) return;

    int trackerId = item->parent()->data(0, Qt::UserRole).toInt();
    Shape* shape = nullptr;
    bool found = false;
    for (Shape* targetShape : *renderShapes) {
        if (targetShape->getTrackerId() == trackerId) {
            shape = targetShape;
            found = true;
            break;
        }
    }
    if (found)
        emit shapeChanged(shape, key, value);
    else
        qDebug() << "[MainWindow::onTreeWidgetItemChanged] shape not found - trackerId:" << trackerId;
    
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
    Square* square = new Square("Square", QPoint(0, 10), QPen(), QBrush(), 100);

    addToShapeTree(square);
}

void MainWindow::on_actionnew_line_button_triggered()
{
    Line* line = new Line("Line", QPoint(0, 10), QPen(), QBrush(), QPoint(0, 10), QPoint(50, 60));

    addToShapeTree(line);
}


void MainWindow::on_actionnew_rectange_button_triggered()
{
    Rectangle* rectangle = new Rectangle("Rectangle", QPoint(0, 10), QPen(), QBrush(), 100, 50);

    addToShapeTree(rectangle);
}


void MainWindow::on_actionnew_circle_button_triggered()
{
    Circle* circle = new Circle("Circle", QPoint(25, 35), QPen(), QBrush(), 25);

    addToShapeTree(circle);
}


void MainWindow::on_actionnew_ellipse_button_triggered()
{
    Ellipse* ellipse = new Ellipse("Ellipse", QPoint(25, 30), QPen(), QBrush(), 25, 20);

    addToShapeTree(ellipse);
}


void MainWindow::on_actionnew_polyline_button_triggered()
{
    Polyline* polyline = new Polyline("Polyline", QPoint(0, 10), QPen(), QBrush(), QPolygon({QPoint(0, 60), QPoint(25, 10), QPoint(50, 60), QPoint(75, 10)}));

    addToShapeTree(polyline);
}


void MainWindow::on_actionnew_polygon_button_triggered()
{
    Polygon* polygon = new Polygon("Polygon", QPoint(0, 10), QPen(), QBrush(), QPolygon({QPoint(0, 60), QPoint(50, 10), QPoint(100, 60), QPoint(50, 45)}));

    addToShapeTree(polygon);
}


void MainWindow::on_actionnew_text_button_triggered()
{
    Text* text = new Text("Text", QPoint(0, 10), "Hello World", Qt::black, Qt::AlignLeft, QFont("Arial", 12), 100, 50);

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
void MainWindow::onLoginClicked() {
    auto *dlg = new LoginWindow(this);
    connect(dlg, &LoginWindow::loginRequested, this, &MainWindow::onLoginRequest);
    connect(dlg, &LoginWindow::signupRequested, this, &MainWindow::onSignupRequest);
    connect(this, &MainWindow::loginSuccess, dlg,  &QDialog::accept);
    dlg->exec();
}

void MainWindow::onLoginRequest(const QString &username, const QString &password) {
    emit loginAttempt(username, password);
}

void MainWindow::onSignupRequest(const QString &username, const QString &password, const bool admin) {
    emit newUserAdded(username, password, admin);
}

void MainWindow::onUserAuthentication(const UserAccount* currUser) {
    this->currUser = currUser;
    userStatusLabel->setText("Logged in as: " + currUser->getUsername());   
    emit loginSuccess();
}

void MainWindow::onUserAuthenticationFailure(const QString &message) {
    emit loginFailed(message);
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
    catch (...) // Added to help programmers debug in future
    {

    }

    renderArea->resetSelection();
}

QComboBox* MainWindow::createAlignmentComboBox(Qt::AlignmentFlag currentAlignment)
{
    QComboBox* box = new QComboBox();
    box->addItem("AlignLeft", static_cast<int>(Qt::AlignLeft));
    box->addItem("AlignRight", static_cast<int>(Qt::AlignRight));
    box->addItem("AlignHCenter", static_cast<int>(Qt::AlignHCenter));
    box->addItem("AlignTop", static_cast<int>(Qt::AlignTop));
    box->addItem("AlignBottom", static_cast<int>(Qt::AlignBottom));
    box->addItem("AlignVCenter", static_cast<int>(Qt::AlignVCenter));
    box->addItem("AlignCenter", static_cast<int>(Qt::AlignCenter));

    // Match currentAlignment to its index
    int index = -1;
    for (int i = 0; i < box->count(); ++i)
    {
        if (box->itemData(i).toInt() == static_cast<int>(currentAlignment))
        {
            index = i;
            break;
        }
    }

    // Set the appropriate index or default to 0 if no match is found
    box->setCurrentIndex(index >= 0 ? index : 0);

    return box;
}


QComboBox* MainWindow::createFontComboBox(QFont currentFont)
{
    QComboBox* box = new QComboBox();
    box->addItem("Arial", 0);
    box->addItem("Times New Roman", 1);
    box->addItem("Courier New", 2);
    box->addItem("Verdana", 3);
    box->addItem("Tahoma", 4);
    box->addItem("Comic Sans MS", 5);

    // This sucks but TOO BAD!!!
    int index = 0;
    if (currentFont.family() == "Arial")
    {
        index = 0;
    }
    else if (currentFont.family() == "Times New Roman")
    {
        index = 1;
    }
    else if (currentFont.family() == "Courier New")
    {
        index = 2;
    }
    else if (currentFont.family() == "Verdana")
    {
        index = 3;
    }
    else if (currentFont.family() == "Tahoma")
    {
        index = 4;
    }
    else if (currentFont.family() == "Comic Sans MS")
    {
        index = 5;
    }

    box->setCurrentIndex(index);
    return box;
}


QComboBox* MainWindow::createFontStyleComboBox(int currentFontStyle)
{
    QComboBox* box = new QComboBox();
    box->addItem("Normal", 0);
    box->addItem("Italic", 1);
    box->addItem("Oblique", 2);
    box->setCurrentIndex(currentFontStyle);
    return box;
}

QComboBox* MainWindow::createFontWeightComboBox(QFont::Weight currentFontWeight)
{
    QComboBox* box = new QComboBox();
    box->addItem("Thin", QFont::Thin);
    box->addItem("Light", QFont::Light);
    box->addItem("Normal", QFont::Normal);
    box->addItem("Bold", QFont::Bold);
    box->addItem("Black", QFont::Black);

    // Match currentFontWeight to its index
    int index = -1;
    for (int i = 0; i < box->count(); ++i)
    {
        if (box->itemData(i).toInt() == static_cast<int>(currentFontWeight))
        {
            index = i;
            break;
        }
    }

    // Set the appropriate index or default to 0 if no match is found
    box->setCurrentIndex(index >= 0 ? index : 0);

    return box;
}

void MainWindow::selection_sort(alpha::vector<Shape*>& shapes, bool (*compare)(const Shape*, const Shape*), bool ascending) {
    for (size_t i = 0; i < shapes.size(); ++i) {
        size_t targetIdx = i;
        for (size_t j = i + 1; j < shapes.size(); ++j) {
            if (ascending ? compare(shapes[j], shapes[targetIdx]) : compare(shapes[targetIdx], shapes[j])) {
                targetIdx = j;
            }
        }
        if (targetIdx != i) {
            std::swap(shapes[i], shapes[targetIdx]);
        }
    }
}

// Comparison functions
bool MainWindow::sortById(const Shape* a, const Shape* b) {
    return a->getShapeId() > b->getShapeId();
}

bool MainWindow::sortByArea(const Shape* a, const Shape* b) {
    return a->Area() > b->Area();
}

bool MainWindow::sortByPerimeter(const Shape* a, const Shape* b) {
    return a->Perimeter() > b->Perimeter();
}
 
// Populate the shape table with shape data
void MainWindow::populateShapeTable(const alpha::vector<Shape*>& shapes) {
    shapeTable->setRowCount(shapes.size());
    for (size_t i = 0; i < shapes.size(); ++i) {
        // Use actual shape ID instead of sequential numbers
        QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(shapes[i]->getShapeId()));
        
        QTableWidgetItem* typeItem = new QTableWidgetItem(QString::fromStdString(shapes[i]->getShapeType()));
        QTableWidgetItem* areaItem = new QTableWidgetItem(QString::number(shapes[i]->Area()));
        QTableWidgetItem* perimeterItem = new QTableWidgetItem(QString::number(shapes[i]->Perimeter()));

        // Make the items uneditable
        idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
        typeItem->setFlags(typeItem->flags() & ~Qt::ItemIsEditable);
        areaItem->setFlags(areaItem->flags() & ~Qt::ItemIsEditable);
        perimeterItem->setFlags(perimeterItem->flags() & ~Qt::ItemIsEditable);

        shapeTable->setItem(i, 0, idItem);
        shapeTable->setItem(i, 1, typeItem);
        shapeTable->setItem(i, 2, areaItem);
        shapeTable->setItem(i, 3, perimeterItem);
    }
}
void MainWindow::createShapeTableTab() {
    // Create a new window for the shape report
    QWidget* reportWindow = new QWidget();
    reportWindow->setWindowTitle("Render Area Shape Report");
    reportWindow->setAttribute(Qt::WA_DeleteOnClose); // Automatically delete the window when closed
    reportWindow->resize(600, 400); // Set an initial size for the window

    // Create a layout for the window
    QVBoxLayout* layout = new QVBoxLayout(reportWindow);

    // Create the dropdown for sorting methods
    sortDropdown = new QComboBox(reportWindow);
    sortDropdown->addItem("Sort by ID");
    sortDropdown->addItem("Sort by Area");
    sortDropdown->addItem("Sort by Perimeter");

    // Create the dropdown for sorting order
    sortOrderDropdown = new QComboBox(reportWindow);
    sortOrderDropdown->addItem("Ascending");
    sortOrderDropdown->addItem("Descending");

    // Ensure the dropdown menus close automatically after selection
    sortDropdown->view()->setSelectionMode(QAbstractItemView::SingleSelection);
    sortDropdown->setEditable(false);
    sortOrderDropdown->view()->setSelectionMode(QAbstractItemView::SingleSelection);
    sortOrderDropdown->setEditable(false);

    layout->addWidget(sortDropdown);
    layout->addWidget(sortOrderDropdown);

    // Connect the dropdowns to the sorting slot
    connect(sortDropdown, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onSortMethodChanged);
    connect(sortOrderDropdown, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onSortMethodChanged);

    // Create the table to display shapes
    shapeTable = new QTableWidget(reportWindow);
    shapeTable->setColumnCount(4);
    shapeTable->setHorizontalHeaderLabels({"Shape ID", "Shape Type", "Area", "Perimeter"});
    shapeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    // Turn off alternating row colors for consistent appearance
    shapeTable->setAlternatingRowColors(false);
    
    // Add grid lines to make table data more readable
    shapeTable->setShowGrid(true);
    shapeTable->setGridStyle(Qt::SolidLine);
    
    // Add border around the table for better definition
    shapeTable->setFrameStyle(QFrame::Box | QFrame::Plain);
    shapeTable->setFrameShape(QFrame::Box);
    shapeTable->setLineWidth(1);
    
    // Use the application's current color scheme to ensure readability in all themes
    QPalette palette = shapeTable->palette();
    palette.setColor(QPalette::Base, palette.color(QPalette::Window));      // Match window background
    palette.setColor(QPalette::Text, palette.color(QPalette::WindowText));  // Match window text color
    palette.setColor(QPalette::Highlight, Qt::darkBlue);                    // Consistent selection color
    palette.setColor(QPalette::HighlightedText, Qt::white);                 // Readable selected text
    shapeTable->setPalette(palette);
    
    layout->addWidget(shapeTable);
    
    // Populate the table with the initial data
    auto shapesCopy = *renderShapes; // Make a copy of the shapes
    selection_sort(shapesCopy, sortById, true); // Default sorting by ID in ascending order
    populateShapeTable(shapesCopy);

    // Set the layout and show the window
    reportWindow->setLayout(layout);
    reportWindow->show();
}

void MainWindow::onSortMethodChanged(int) {
    // Create a copy of shapes to sort without affecting the original data
    auto shapesCopy = *renderShapes;
    alpha::vector<Shape*> filteredShapes;
    
    // Determine the sorting method
    bool ascending = (sortOrderDropdown->currentIndex() == 0);
    
    switch (sortDropdown->currentIndex()) {
        case 0: // Sort by ID
            filteredShapes = shapesCopy;
            selection_sort(filteredShapes, sortById, ascending);
            break;
        case 1: // Sort by Area
            // Only include shapes with valid area (greater than 0)
            for (Shape* shape : shapesCopy) {
                if (shape->Area() > 0) {
                    filteredShapes.push_back(shape);
                }
            }
            selection_sort(filteredShapes, sortByArea, ascending);
            break;
        case 2: // Sort by Perimeter
            // Only include shapes with valid perimeter (greater than 0)
            for (Shape* shape : shapesCopy) {
                if (shape->Perimeter() > 0) {
                    filteredShapes.push_back(shape);
                }
            }
            selection_sort(filteredShapes, sortByPerimeter, ascending);
            break;
    }
 
    // Update the displayed table with filtered and sorted data
    populateShapeTable(filteredShapes);
}