#include "shape.h"

/****************************************************
* class Shape - Abstract Base Class
*****************************************************/

Shape::Shape(int    shapeId,
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
    parentItem->setText(0, QString::fromStdString(shapeType));

    for (int i = 0; i < 5; ++i) // 5 being # of data members in shape being displayed for all shapes (JUST FOR TESTING PLEASE CHANGE)
    {
        childItems.push_back(new QTreeWidgetItem());
        parentItem->addChild(childItems[i]);
    }
    // hard coded spaces for each subitem, change as you please
    childItems[0]->setText(0, "Shape Id:");
    childItems[1]->setText(0, "Shape Type:");
    childItems[2]->setText(0, "Pen:");
    childItems[3]->setText(0, "Brush:");
    childItems[4]->setText(0, "Coords:");
}

Shape::~Shape() {}

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
void Shape::setTrackerId(int trackerId)    { this->trackerId = trackerId; }
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
