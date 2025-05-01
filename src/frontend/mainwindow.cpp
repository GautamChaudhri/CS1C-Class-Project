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
    int trackerId;

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

        // Tag each combo box with the shape's trackerId and a key for easy shape modifications
        trackerId = item->getTrackerId();
        penStyleCombo->setProperty("trackerId", trackerId);
        penStyleCombo->setProperty("key",        QStringLiteral("Pen:"));
        brushStyleCombo->setProperty("trackerId", trackerId);
        brushStyleCombo->setProperty("key",        QStringLiteral("Brush:"));

        // Connect the combo boxes to slot to handle shape change after a new value is chosen
        connect(penStyleCombo, &QComboBox::currentIndexChanged, this, &MainWindow::onComboBoxChanged);
        connect(brushStyleCombo, &QComboBox::currentIndexChanged, this, &MainWindow::onComboBoxChanged);

        // Add top-level item to the tree widget
        ui->treeWidget->addTopLevelItem(item->getParentItem());
        item->getParentItem()->setData(0, Qt::UserRole, QVariant::fromValue(item->getTrackerId()));

        switch (item->getShapeId())
        {
        case LINE:
            ui->treeWidget->setItemWidget(item->getChildItems()[item->getChildEnd()], 1, penStyleCombo);
            break;

        case POLYLINE:
            ui->treeWidget->setItemWidget(item->getChildItems()[item->getChildEnd()], 1, penStyleCombo);
            break;

        case POLYGON:
            ui->treeWidget->setItemWidget(item->getChildItems()[item->getChildEnd() - 1], 1, penStyleCombo);
            ui->treeWidget->setItemWidget(item->getChildItems()[item->getChildEnd()], 1,     brushStyleCombo);
            break;

        case RECTANGLE:
            ui->treeWidget->setItemWidget(item->getChildItems()[item->getChildEnd() - 1], 1, penStyleCombo);
            ui->treeWidget->setItemWidget(item->getChildItems()[item->getChildEnd()], 1,     brushStyleCombo);
            break;

        case SQUARE:
            ui->treeWidget->setItemWidget(item->getChildItems()[item->getChildEnd() - 1], 1, penStyleCombo);
            ui->treeWidget->setItemWidget(item->getChildItems()[item->getChildEnd()], 1,     brushStyleCombo);
            break;

        case ELLIPSE:
            ui->treeWidget->setItemWidget(item->getChildItems()[item->getChildEnd() - 1], 1, penStyleCombo);
            ui->treeWidget->setItemWidget(item->getChildItems()[item->getChildEnd()], 1,     brushStyleCombo);
            break;

        case CIRCLE:
            ui->treeWidget->setItemWidget(item->getChildItems()[item->getChildEnd() - 1], 1, penStyleCombo);
            ui->treeWidget->setItemWidget(item->getChildItems()[item->getChildEnd()], 1,     brushStyleCombo);
            break;

        case TEXT:
            Text* text = static_cast<Text*>(item);

            QComboBox* alignmentCombo  = createAlignmentComboBox(text->getTextAlignment());
            QComboBox* fontCombo       = createFontComboBox(text->getFont());
            QComboBox* fontStyleCombo  = createFontStyleComboBox(text->getFontStyle());
            QComboBox* fontWeightCombo = createFontWeightComboBox(text->getFontWeight());

            // Tagging the boxes for easy modification 
            alignmentCombo->setParent(ui->treeWidget);
            alignmentCombo->setProperty("trackerId", trackerId);
            alignmentCombo->setProperty("key", QStringLiteral("Alignment:"));
            connect(alignmentCombo, &QComboBox::currentIndexChanged, this, &MainWindow::onComboBoxChanged);

            fontCombo->setParent(ui->treeWidget);
            fontCombo->setProperty("trackerId", trackerId);
            fontCombo->setProperty("key", QStringLiteral("Font:"));
            connect(fontCombo, &QComboBox::currentIndexChanged, this, &MainWindow::onComboBoxChanged);

            fontStyleCombo->setParent(ui->treeWidget);
            fontStyleCombo->setProperty("trackerId", trackerId);
            fontStyleCombo->setProperty("key", QStringLiteral("FontStyle:"));
            connect(fontStyleCombo, &QComboBox::currentIndexChanged, this, &MainWindow::onComboBoxChanged);

            fontWeightCombo->setParent(ui->treeWidget);
            fontWeightCombo->setProperty("trackerId", trackerId);
            fontWeightCombo->setProperty("key", QStringLiteral("FontWeight:"));
            connect(fontWeightCombo, &QComboBox::currentIndexChanged, this, &MainWindow::onComboBoxChanged);

            ui->treeWidget->setItemWidget(item->getChildItems()[item->getChildEnd() - 3], 1, alignmentCombo);
            ui->treeWidget->setItemWidget(item->getChildItems()[item->getChildEnd() - 2], 1, fontCombo);
            ui->treeWidget->setItemWidget(item->getChildItems()[item->getChildEnd() - 1], 1, fontStyleCombo);
            ui->treeWidget->setItemWidget(item->getChildItems()[item->getChildEnd()], 1,     fontWeightCombo);
            break;
        }
    }
}

void MainWindow::onTreeWidgetItemChanged(QTreeWidgetItem* item, int column) {
    // Only proceed if changes made occurred in column 1
    if (column != 1) return;

    QString key = item->text(0);
    
    // Handle edits to the displayed text in a Text Object seperately
    if (key == "Text:") {
        QString newText = item->text(1);
        // find the top-level item to get the trackerId
        QTreeWidgetItem* root = item;
        while (root->parent()) root = root->parent();
        int trackerId = root->data(0, Qt::UserRole).toInt();

        // lookup the Text* in our shapes list
        Text* textObj = nullptr;
        for (Shape* shape : *renderShapes) {
            if (shape->getTrackerId() == trackerId) {
                textObj = static_cast<Text*>(shape);
                break;
            }
        }
        if (textObj) {
            emit displayedTextChanged(textObj, newText);
        } else {
            qDebug() << "[onTreeWidgetItemChanged] text shape not found for trackerId" << trackerId;
        }
        return;
    }

    bool ok = false;
    int value = item->text(1).toInt(&ok);
    if (!ok) return;

    // Climb to the top-most parent to get the root shape item
    QTreeWidgetItem* parentItem = item;
    while (parentItem->parent())
        parentItem = parentItem->parent();

    int trackerId = parentItem->data(0, Qt::UserRole).toInt();
    Shape* shape = nullptr;
    bool found = false;
    for (Shape* targetShape : *renderShapes) {
        if (targetShape->getTrackerId() == trackerId) {
            found = true;
            shape = targetShape;
            emit shapeChanged(shape, key, value);
            break;
        }
    }

    if (!found)
        qDebug() << "[MainWindow::onTreeWidgetItemChanged] shape not found - trackerId: " + trackerId;

}

void MainWindow::onComboBoxChanged(int newIndex) {
    int trackerId;
    QString key;
    int newValue;
    Shape* shape = nullptr;
    
    // Determine which QComboBox sent the changed signal
    QComboBox* combo = qobject_cast<QComboBox*>(sender());
    if (!combo)
        return;

    // Grab the key and trackerId that we tagged on to each combo box
    trackerId = combo->property("trackerId").toInt();
    key = combo->property("key").toString();

    // Get the new value that was changed
    newValue = combo->itemData(newIndex).toInt();

    // Find the pointer to the shape that needs to be changed
    bool found = false;
    for (Shape* targetShape : *renderShapes) {
        if (targetShape->getTrackerId() == trackerId) {
            found = true;
            shape = targetShape;
            emit shapeChanged(shape, key, newValue);
            break;
        }
    }

    if (!found)
        qDebug() << "[MainWindow::onComboBoxChanged] shape not found - trackerId: " + trackerId;

}

void MainWindow::onRenderAreaChanged() {
    //update();
    renderArea->update();
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

    // // Pick the index whose data matches our currentBrushStyle
    // for (int i = 0; i < box->count(); ++i) {
    //     if (box->itemData(i).toInt() == currentBrushStyle) {
    //         box->setCurrentIndex(i);
    //         break;
    //     }
    // }
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

    ui->toolBar->setEnabled(currUser->isAdmin()); //allows admin accounts to edit shapes
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



