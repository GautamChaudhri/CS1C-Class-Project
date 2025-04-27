#include "shape.h"
#include <QComboBox>

/****************************************************
* class Shape - Abstract Base Class
*****************************************************/

Shape::Shape(int    trackerId,
             string shapeType,
             QPoint coords,
             QPen   pen,
             QBrush brush)
           : trackerId{trackerId},
             shapeType{shapeType},
             coords{coords},
             pen{pen},
             brush{brush},
             parentItem{new QTreeWidgetItem()}
{
    parentItem->setText(0, QString::fromStdString(shapeType));

    for (int i = 0; i < 7; ++i) // 6 being # of data members in shape being displayed for all shapes (JUST FOR TESTING PLEASE CHANGE)
    {
        childItems.push_back(new QTreeWidgetItem());
        parentItem->addChild(childItems[i]);
    }
    // hard coded spaces for each subitem, change as you please
    childItems[0]->setText(0, "Shape ID:");
    childItems[0]->setText(1, QString::number(getShapeId()));

    childItems[1]->setText(0, "Tracker ID:");
    childItems[1]->setText(1, QString::number(getTrackerId()));

    childItems[2]->setText(0, "Shape Type:");
    childItems[2]->setText(1, QString::fromStdString(shapeType));

    childItems[3]->setText(0, "X:");
    childItems[3]->setText(1, QString::number(getX()));
    childItems[3]->setFlags(childItems[3]->flags() | Qt::ItemIsEditable);

    childItems[4]->setText(0, "Y:");
    childItems[4]->setText(1, QString::number(getY()));
    childItems[4]->setFlags(childItems[4]->flags() | Qt::ItemIsEditable);
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
void Shape::setTrackerId(int trackerId)    { /*this->trackerId = trackerId;*/} //This causes issues
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
