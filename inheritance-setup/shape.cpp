#include "shape.h"

/****************************************************
* class Shape - Abstract Base Class
*****************************************************/

Shape::Shape(int          shapeId,
             std::string       shapeType,
             int          x,
             int          y,
             Qt::GlobalColor  penColor,
             int          penWidth,
             Qt::PenStyle     penStyle,
             Qt::PenCapStyle  penCapStyle,
             Qt::PenJoinStyle penJoinStyle,
             Qt::GlobalColor  brushColor,
             Qt::BrushStyle   brushStyle)
    : shapeId{shapeId},
    shapeType{shapeType},
    x{x},
    y{y},
    penColor{penColor},
    penWidth{penWidth},
    penStyle{penStyle},
    penCapStyle{penCapStyle},
    penJoinStyle{penJoinStyle},
    brushColor{brushColor},
    brushStyle{brushStyle}
{}

Shape::~Shape() {}

void Shape::Move(int x, int y)
{
    this->x = x;
    this->y = y;
}

/**************** ACCESSOR FUNCTIONS ****************/
int    Shape::getShapeId()   const { return shapeId; }
int    Shape::getTrackerId() const { return trackerId; }
string Shape::getShapeType() const { return shapeType; }

int Shape::getX() const { return x; }
int Shape::getY() const { return y; }

int              Shape::getPenWidth()     const { return penWidth; }
Qt::PenStyle     Shape::getPenStyle()     const { return penStyle; }
Qt::PenCapStyle  Shape::getPenCapStyle()  const { return penCapStyle; }
Qt::PenJoinStyle Shape::getPenJoinStyle() const { return penJoinStyle; }
Qt::GlobalColor  Shape::getBrushColor()   const { return brushColor; }
Qt::BrushStyle   Shape::getBrushStyle()   const { return brushStyle; }
/****************************************************/

/***************** MUTATOR FUNCTIONS ****************/
void Shape::setShapeId(int shapeId)        { this->shapeId   = shapeId; }
void Shape::setTrackerId(int trackerId)    { this->trackerId = trackerId; }
void Shape::setShapeType(string shapeType) { this->shapeType = shapeType; }

void Shape::setX(int x) { this->x = x; }
void Shape::setY(int y) { this->y = y; }

void Shape::setPenWidth(int penWidth)                      { this->penWidth     = penWidth; }
void Shape::setPenStyle(Qt::PenStyle penStyle)             { this->penStyle     = penStyle; }
void Shape::setPenCapStyle(Qt::PenCapStyle penCapStyle)    { this->penCapStyle  = penCapStyle; }
void Shape::setPenJoinStyle(Qt::PenJoinStyle penJoinStyle) { this->penJoinStyle = penJoinStyle; }
void Shape::setBrushColor(Qt::GlobalColor brushColor)      { this->brushColor   = brushColor; }
void Shape::setBrushStyle(Qt::BrushStyle brushStyle)       { this->brushStyle   = brushStyle; }
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

/****************************************************/
