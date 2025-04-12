#include "ellipse.h"

/****************************************************
* class Ellipse - Derived Class
*****************************************************/

Ellipse::Ellipse(int    shapeId,
                  string shapeType,
                  QPoint coords,
                  QPen   pen,
                  QBrush brush,
                  int    a,
                  int    b)
                 : Shape(shapeId,
                         shapeType,
                         coords,
                         pen,
                         brush),
                 a{a},
                 b{b}
{}

void Ellipse::Draw()
{
    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawEllipse(getPoints(), a, b);
    getPainter().restore();
}

double Ellipse::Perimeter() const { return 2 * PI * sqrt((pow((2 * a), 2) + pow((2 * b), 2)) / 2); }
double Ellipse::Area()      const { return PI * a * b; }

/****************************************************/

