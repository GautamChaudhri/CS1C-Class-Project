#include "line.h"

/****************************************************
* class Line - Derived Class
*****************************************************/

Line::Line(int          shapeId,
           std::string       shapeType,
           int          x,
           int          y,
           Qt::GlobalColor  penColor,
           int          penWidth,
           Qt::PenStyle     penStyle,
           Qt::PenCapStyle  penCapStyle,
           Qt::PenJoinStyle penJoinStyle,
           int          x1,
           int          y1,
           int          x2,
           int          y2)
    : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle,
            penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
    x1{x1},
    y1{y1},
    x2{x2},
    y2{y2}
{}

double Line::Perimeter() const
{
    return sqrt(pow((x1 - x2),2) + pow((y1 - y2), 2));
}
