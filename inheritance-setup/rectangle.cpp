#include "rectangle.h"

/****************************************************
* class Rectangle - Derived Class
*****************************************************/

Rectangle::Rectangle(int          shapeId,
                     std::string       shapeType,
                     int          x,
                     int          y,
                     Qt::GlobalColor  penColor,
                     int          penWidth,
                     Qt::PenStyle     penStyle,
                     Qt::PenCapStyle  penCapStyle,
                     Qt::PenJoinStyle penJoinStyle,
                     int          length,
                     int          width)
    : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle,
            penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
    length{length},
    width{width}
{}


double Rectangle::Perimeter() const { return (length * 2) + (width * 2); }
double Rectangle::Area()      const { return length * width; }

/****************************************************/
