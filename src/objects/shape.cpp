#include "shape.h"
#include <QComboBox>

/****************************************************
 * Static Initialization
*****************************************************/
int Shape::nextTracker[9] = {};     // Default initialized to all zeros
bool Shape::trackersInUse[9000] = {}; // Default initialized to all false

// One-time static initialization of tracker arrays
namespace {
struct TrackerLogicInit {
    TrackerLogicInit() {
        // Initialize nextTracker for each shape type
        Shape::nextTracker[0] = 0;
        for (int i = 1; i < 9; ++i)
            Shape::nextTracker[i] = i * 1000;

        // Reserve all IDs 0–999: never hand them out
        for (int i = 0; i < 1000; ++i)
            Shape::trackersInUse[i] = true;
        // Make IDs 1000–8999 available
        for (int i = 1000; i < 9000; ++i)
            Shape::trackersInUse[i] = false;
    }
} trackerLogicInit;
}


/****************************************************
* class Shape - Abstract Base Class
*****************************************************/

Shape::Shape(int shapeId,
             string shapeType,
             QPoint coords,
             QPen   pen,
             QBrush brush)
           : shapeId{shapeId},
             shapeType{shapeType},
             coords{coords},
             pen{pen},
             brush{brush},
             parentItem{new QTreeWidgetItem()}
{
    allocateTrackerId(shapeId);
}

Shape::~Shape()
{
    delete parentItem;
}

void Shape::Move(int x, int y)
{
    setX(x);
    setY(y);
}

void Shape::CreateParentItem()
{
    parentItem->setText(0, QString::fromStdString(shapeType));

    childItems.push_back(new QTreeWidgetItem());
    parentItem->addChild(*(childItems.end() - 1));
    (*(childItems.end() - 1))->setText(0, "Shape ID:");
    (*(childItems.end() - 1))->setText(1, QString::number(getShapeId()));

    childItems.push_back(new QTreeWidgetItem());
    parentItem->addChild(*(childItems.end() - 1));
    (*(childItems.end() - 1))->setText(0, "Tracker ID:");
    (*(childItems.end() - 1))->setText(1, QString::number(getTrackerId()));

    childItems.push_back(new QTreeWidgetItem());
    parentItem->addChild(*(childItems.end() - 1));
    (*(childItems.end() - 1))->setText(0, "X:");
    (*(childItems.end() - 1))->setText(1, QString::number(getX()));
    (*(childItems.end() - 1))->setFlags((*(childItems.end() - 1))->flags() | Qt::ItemIsEditable);

    childItems.push_back(new QTreeWidgetItem());
    parentItem->addChild(*(childItems.end() - 1));
    (*(childItems.end() - 1))->setText(0, "Y:");
    (*(childItems.end() - 1))->setText(1, QString::number(getY()));
    (*(childItems.end() - 1))->setFlags((*(childItems.end() - 1))->flags() | Qt::ItemIsEditable);
}

void Shape::CreatePenChild()
{
    childItems.push_back(new QTreeWidgetItem());
    auto endChild = (*(childItems.end() - 1));

    parentItem->addChild(endChild);
    endChild->setText(0, "Pen:");

    //endChild->setFlags(endChild->flags() & ~Qt::ItemIsEditable);

    // Pen Color
    penItems.push_back(new QTreeWidgetItem());
    endChild->addChild(*(penItems.end() - 1));
    (*(penItems.end() -1))->setText(0, "PenColor:");
    (*(penItems.end() -1))->setFlags((*(penItems.end() - 1))->flags() | Qt::ItemIsEditable);

    QString penColor;
    if (pen.color() == Qt::red)
        penColor = "red";
    else if (pen.color() == Qt::green)
        penColor = "green";
    else if (pen.color() == Qt::yellow)
        penColor = "yellow";
    else if (pen.color() == Qt::cyan)
        penColor = "cyan";
    else if (pen.color() == Qt::magenta)
        penColor = "magenta";
    else if (pen.color() == Qt::gray)
        penColor = "gray";
    else if (pen.color() == Qt::blue)
        penColor = "blue";
    else if (pen.color() == Qt::white)
        penColor = "white";
    else if (pen.color() == Qt::lightGray)
        penColor = "lightGray";
    else if (pen.color() == Qt::darkGray)
        penColor = "darkGray";
    else if (pen.color() == Qt::black)
        penColor = "black";
    else if (pen.color() == Qt::transparent)
        penColor = "transparent";
    else
        qDebug() << "[Shape::CreatePenChild] PenColor Error";
    (*(penItems.end() - 1))->setText(1, penColor);

    // Pen Width
    penItems.push_back(new QTreeWidgetItem());
    endChild->addChild(*(penItems.end() - 1));
    (*(penItems.end() -1))->setText(0, "PenWidth:");
    (*(penItems.end() -1))->setText(1, QString::number(pen.width()));
    (*(penItems.end() -1))->setFlags((*(penItems.end() - 1))->flags() | Qt::ItemIsEditable);

    // Pen Style
    penItems.push_back(new QTreeWidgetItem());
    endChild->addChild(*(penItems.end() - 1));
    (*(penItems.end() -1))->setText(0, "PenStyle:");
    (*(penItems.end() -1))->setFlags((*(penItems.end() - 1))->flags() | Qt::ItemIsEditable);

    QString penStyle;
    if (pen.style() == Qt::SolidLine)
        penStyle = "SolidLine";
    else if (pen.style() == Qt::DashLine)
        penStyle = "DashLine";
    else if (pen.style() == Qt::DotLine)
        penStyle = "DotLine";
    else if (pen.style() == Qt::DashDotLine)
        penStyle = "DashDotLine";
    else if (pen.style() == Qt::DashDotDotLine)
        penStyle = "DashDotDotLine";
    else
        qDebug() << "[Shape::CreatePenChild] PenStyle Error";

    (*(penItems.end() - 1))->setText(1, penStyle);

    // Pen Cap Style
    penItems.push_back(new QTreeWidgetItem());
    endChild->addChild(*(penItems.end() - 1));
    (*(penItems.end() -1))->setText(0, "PenCapStyle:");
    (*(penItems.end() -1))->setFlags((*(penItems.end() - 1))->flags() | Qt::ItemIsEditable);

    QString penCapStyle;
    if (pen.capStyle() == Qt::FlatCap)
        penCapStyle = "FlatCap";
    else if (pen.capStyle() == Qt::SquareCap)
        penCapStyle = "SquareCap";
    else if (pen.capStyle() == Qt::RoundCap)
        penCapStyle = "RoundCap";
    else
        qDebug() << "[Shape::CreatePenChild] PenCapStyle Error";

    (*(penItems.end() - 1))->setText(1, penCapStyle);


    // Pen Join Style
    penItems.push_back(new QTreeWidgetItem());
    endChild->addChild(*(penItems.end() - 1));
    (*(penItems.end() -1))->setText(0, "PenJoinStyle:");
    (*(penItems.end() -1))->setFlags((*(penItems.end() - 1))->flags() | Qt::ItemIsEditable);

    QString penJoinStyle;
    if (pen.joinStyle() == Qt::MiterJoin)
        penJoinStyle = "MiterJoin";
    else if (pen.joinStyle() == Qt::BevelJoin)
        penJoinStyle = "BevelJoin";
    else if (pen.joinStyle() == Qt::RoundJoin)
        penJoinStyle = "RoundJoin";
    else
        qDebug() << "[Shape::CreatePenChild] PenJoinStyle Error";

    (*(penItems.end() - 1))->setText(1, penJoinStyle);

}

void Shape::CreateBrushChild()
{
    childItems.push_back(new QTreeWidgetItem());
    auto endChild = (*(childItems.end() - 1));

    parentItem->addChild(endChild);
    endChild->setText(0, "Brush:");

    //endChild->setFlags(endChild->flags() & ~Qt::ItemIsEditable);

    // Brush Color
    brushItems.push_back(new QTreeWidgetItem());
    endChild->addChild(*(brushItems.end() - 1));
    (*(brushItems.end() - 1))->setText(0, "BrushColor:");

    QString brushColor;
    if (brush.color() == Qt::red)
        brushColor = "red";
    else if (brush.color() == Qt::green)
        brushColor = "green";
    else if (brush.color() == Qt::yellow)
        brushColor = "yellow";
    else if (brush.color() == Qt::cyan)
        brushColor = "cyan";
    else if (brush.color() == Qt::magenta)
        brushColor = "magenta";
    else if (brush.color() == Qt::gray)
        brushColor = "gray";
    else if (brush.color() == Qt::blue)
        brushColor = "blue";
    else if (brush.color() == Qt::white)
        brushColor = "white";
    else if (brush.color() == Qt::lightGray)
        brushColor = "lightGray";
    else if (brush.color() == Qt::darkGray)
        brushColor = "darkGray";
    else if (brush.color() == Qt::black)
        brushColor = "black";
    else if (brush.color() == Qt::transparent)
        brushColor = "transparent";
    else
        qDebug() << "[Shape::CreateBrushChild] BrushColor Error";

    (*(brushItems.end() - 1))->setText(1, brushColor);

    // Brush Style
    brushItems.push_back(new QTreeWidgetItem());
    endChild->addChild(*(brushItems.end() - 1));
    (*(brushItems.end() - 1))->setText(0, "BrushStyle:");

    QString brushStyle;
    switch (brush.style()) {
        case Qt::NoBrush:         brushStyle = "NoBrush";       break;
        case Qt::SolidPattern:    brushStyle = "SolidPattern";  break;
        case Qt::Dense1Pattern:   brushStyle = "Dense1Pattern"; break;
        case Qt::Dense2Pattern:   brushStyle = "Dense2Pattern"; break;
        case Qt::Dense3Pattern:   brushStyle = "Dense3Pattern"; break;
        case Qt::Dense4Pattern:   brushStyle = "Dense4Pattern"; break;
        case Qt::Dense5Pattern:   brushStyle = "Dense5Pattern"; break;
        case Qt::Dense6Pattern:   brushStyle = "Dense6Pattern"; break;
        case Qt::Dense7Pattern:   brushStyle = "Dense7Pattern"; break;
        case Qt::HorPattern:      brushStyle = "HorPattern";    break;
        case Qt::VerPattern:      brushStyle = "VerPattern";    break;
        case Qt::CrossPattern:    brushStyle = "CrossPattern";  break;
        case Qt::BDiagPattern:    brushStyle = "BDiagPattern";  break;
        case Qt::FDiagPattern:    brushStyle = "FDiagPattern";  break;
        case Qt::DiagCrossPattern:brushStyle = "DiagCrossPattern"; break;
        default:
            qDebug() << "[Shape::CreateBrushChild] BrushStyle Error";
    }

    (*(brushItems.end() - 1))->setText(1, brushStyle);
}

void Shape::CreatePointsChild(const int POINTS_NUM)
{
    childItems.push_back(new QTreeWidgetItem());
    parentItem->addChild(*(childItems.end() - 1));
    (*(childItems.end() - 1))->setText(0, "Points:");

    for (int i = 0; i < (POINTS_NUM); ++i)
    {
        pointsItems.push_back(new QTreeWidgetItem());
        (*(childItems.end() - 1))->addChild(*(pointsItems.end() - 1));
        (*(pointsItems.end() - 1))->setText(0, "X" + QString::number(i + 1) + ":");
        (*(pointsItems.end() - 1))->setText(1, QString::number(getX()));
        (*(pointsItems.end() - 1))->setFlags((*(pointsItems.end() - 1))->flags() | Qt::ItemIsEditable);

        pointsItems.push_back(new QTreeWidgetItem());
        (*(childItems.end() - 1))->addChild(*(pointsItems.end() - 1));
        (*(pointsItems.end() - 1))->setText(0, "Y" + QString::number(i + 1) + ":");
        (*(pointsItems.end() - 1))->setText(1, QString::number(getY()));
        (*(pointsItems.end() - 1))->setFlags((*(pointsItems.end() - 1))->flags() | Qt::ItemIsEditable);
    }
}


/**************** ACCESSOR FUNCTIONS ****************/
int    Shape::getShapeId()   const { return shapeId; }
int    Shape::getTrackerId() const { return trackerId; }
string Shape::getShapeType() const { return shapeType; }
bool   Shape::getSelected()  const { return isSelected; }

int Shape::getX() const { return coords.x(); }
int Shape::getY() const { return coords.y(); }

QPainter& Shape::getPainter() { return painter; }
QTreeWidgetItem* Shape::getParentItem() { return parentItem; }
alpha::vector<QTreeWidgetItem*>& Shape::getChildItems()  { return childItems; }
alpha::vector<QTreeWidgetItem*>& Shape::getPointsItems() { return pointsItems; }
alpha::vector<QTreeWidgetItem*>& Shape::getPenItems()    { return penItems; }
alpha::vector<QTreeWidgetItem*>& Shape::getBrushItems()  { return brushItems; }

int          Shape::getPenWidth()      const { return pen.width(); }
PenStyle     Shape::getPenStyle()      const { return pen.style(); }
PenCapStyle  Shape::getPenCapStyle()   const { return pen.capStyle(); }
PenJoinStyle Shape::getPenJoinStyle()  const { return pen.joinStyle(); }
QColor       Shape::getPenColor()      const { return pen.color(); }
QColor       Shape::getBrushColor()    const { return brush.color(); }
BrushStyle   Shape::getBrushStyle()    const { return brush.style(); }
QPen         Shape::getPen()           const { return pen; }
QBrush       Shape::getBrush()         const { return brush; }
QPoint       Shape::getPoints()        const { return coords;}
int          Shape::getChildEnd()      const { return std::distance(childItems.begin(), childItems.end()) - 1; }
int          Shape::getPenItemsEnd()   const { return std::distance(penItems.begin(),   penItems.end())   - 1; }
int          Shape::getBrushItemsEnd() const { return std::distance(brushItems.begin(), brushItems.end()) - 1; }
/****************************************************/

/***************** MUTATOR FUNCTIONS ****************/
void Shape::setShapeType(string shapeType) { this->shapeType = shapeType; }
void Shape::setSelected(bool selected)     { isSelected = selected;}

void Shape::setTrackerId(int desiredId) {
    // If desiredId is in valid range and not already in use, assign it directly
    if (desiredId >= 0 && desiredId < 9000 && !trackersInUse[desiredId]) {
        trackersInUse[desiredId] = true;
        trackerId = desiredId;
        // Advance nextTracker for this shape type if needed
        int type = shapeId;
        if (nextTracker[type] <= desiredId) {
            nextTracker[type] = desiredId + 1;
        }
    } else {
        // desiredId was in use or out of range: allocate the next free ID
        qDebug() << "[Shape::setTrackerId] Desired ID " << desiredId 
               << " is in use or out of range. Allocating a new tracker ID.";
        allocateTrackerId(shapeId);
    }
    // After assigning trackerId, refresh the tree widget entry:
    for (auto item : childItems) {
        if (item->text(0) == "Tracker ID:") {
            item->setText(1, QString::number(trackerId));
            break;
        }
    }
}

void Shape::allocateTrackerId(int shapeId) {
    int potentialId;
    bool idFound = false;

    while (!idFound) {
        potentialId = nextTracker[shapeId];

        if (trackersInUse[potentialId])         //check to see if next trackerId is already in use
            nextTracker[shapeId]++;             //if in use, increment trackerId and loop to check again
        else {                                  
            trackersInUse[potentialId] = true;  //when unused trackerId is found, assign it 
            this->trackerId = potentialId;      //and mark it as used 
            idFound = true;
        }
    }
}

void Shape::setX(int x) { coords.rx() = x; }
void Shape::setY(int y) { coords.ry() = y; }

void Shape::setPen(GlobalColor penColor, int penWidth, PenStyle penStyle, PenCapStyle penCapStyle, PenJoinStyle penJoinStyle)
{
    this->pen.setColor(penColor);
    this->pen.setWidth(penWidth);
    this->pen.setStyle(penStyle);
    this->pen.setCapStyle(penCapStyle);
    this->pen.setJoinStyle(penJoinStyle);
}

void Shape::setBrush(Qt::GlobalColor brushColor, Qt::BrushStyle brushStyle)
{
    this->brush.setColor(brushColor);
    this->brush.setStyle(brushStyle);
}

QPen& Shape::setInternalPen() { return pen; }

QBrush& Shape::setInternalBrush() { return brush; }
/****************************************************/

// Overloaded Operators
bool operator==(const Shape& shape1, const Shape& shape2)
{
    return shape1.shapeId == shape2.shapeId;
}

bool operator<(const Shape& shape1, const Shape& shape2)
{
    return shape1.shapeId < shape2.shapeId;
}
/****************************************************/
