#include "shape.h"
#include <QComboBox>

/****************************************************
* class Shape - Abstract Base Class
*****************************************************/

Shape::Shape(string shapeType,
             QPoint coords,
             QPen   pen,
             QBrush brush)
           : shapeType{shapeType},
             coords{coords},
             pen{pen},
             brush{brush},
             parentItem{new QTreeWidgetItem()}
{
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
    auto endChild = (*(childItems.end() - 1));

    childItems.push_back(new QTreeWidgetItem());
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
    auto endChild = (*(childItems.end() - 1));

    childItems.push_back(new QTreeWidgetItem());
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
    // if (brush.style() == Qt::SolidPattern)
    //     brushStyle = "SolidPattern";
    // else if (brush.color() == Qt::VerPattern)
    //     brushColor = "VerPattern";
    // else if (brush.color() == Qt::HorPattern)
    //     brushColor = "HorPattern";
    // else if (brush.color() == Qt::Dense1Pattern)
    //     brushColor = "Dense1Pattern";
    // else if (brush.color() == Qt::CrossPattern)
    //     brushColor = "CrossPattern";
    // else if (brush.color() == Qt::DiagCrossPattern)
    //     brushColor = "DiagCrossPattern";
    // else if (brush.color() == Qt::NoBrush)
    //     brushColor = "NoBrush";
    // else
    //     qDebug() << "[Shape::CreateBrushChild] BrushStyle Error";

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

void Shape::AddPointsToParent(const int POINTS_NUM)
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
alpha::vector<QTreeWidgetItem*>& Shape::getChildItems() { return childItems; }
alpha::vector<QTreeWidgetItem*>& Shape::getPointsItems() { return pointsItems; }

int          Shape::getPenWidth()     const { return pen.width(); }
PenStyle     Shape::getPenStyle()     const { return pen.style(); }
PenCapStyle  Shape::getPenCapStyle()  const { return pen.capStyle(); }
PenJoinStyle Shape::getPenJoinStyle() const { return pen.joinStyle(); }
QColor       Shape::getPenColor()     const { return pen.color(); }
QColor       Shape::getBrushColor()   const { return brush.color(); }
BrushStyle   Shape::getBrushStyle()   const { return brush.style(); }
QPen         Shape::getPen()          const { return pen; }
QBrush       Shape::getBrush()        const { return brush; }
QPoint       Shape::getPoints()       const { return coords;}
int          Shape::getChildEnd()     const { return std::distance(childItems.begin(), childItems.end()) - 1;}
/****************************************************/

/***************** MUTATOR FUNCTIONS ****************/
void Shape::setShapeId(int shapeId)        { this->shapeId   = shapeId; }
void Shape::setTrackerId(int trackerId)    { this->trackerId = trackerId;} //This causes issues
void Shape::setShapeType(string shapeType) { this->shapeType = shapeType; }
void Shape::setSelected(bool selected)     { isSelected = selected;}

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
