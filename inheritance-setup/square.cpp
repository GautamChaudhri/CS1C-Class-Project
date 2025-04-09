#include "square.h"

/****************************************************
* class Square - Derived Class
*****************************************************/

Square::Square(int          shapeId,
               std::string       shapeType,
               int          x,
               int          y,
               Qt::GlobalColor  penColor,
               int          penWidth,
               Qt::PenStyle     penStyle,
               Qt::PenCapStyle  penCapStyle,
               Qt::PenJoinStyle penJoinStyle,
               int          length)
    : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle,
            penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
    length{length}
{}


double Square::Perimeter() const { return length * 4; }
double Square::Area()      const { return pow(length, 2); }

/****************************************************/

