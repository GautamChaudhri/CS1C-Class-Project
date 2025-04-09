#include "ellipse.h"

/****************************************************
* class Ellipse - Derived Class
*****************************************************/

Ellipse::Ellipse(int shapeId,
                 std::string shapeType,
                 int x,
                 int y,
                 Qt::GlobalColor penColor,
                 int penWidth,
                 Qt::PenStyle penStyle,
                 Qt::PenCapStyle penCapStyle,
                 Qt::PenJoinStyle penJoinStyle,
                 int a,
                 int b)
    : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle,
            penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
    a{a},
    b{b}
{}

double Ellipse::Perimeter() const { return 2 * PI * sqrt((pow((2 * a), 2) + pow((2 * b), 2)) / 2); }
double Ellipse::Area()      const { return PI * a * b; }

/****************************************************/

