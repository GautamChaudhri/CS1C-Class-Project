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
