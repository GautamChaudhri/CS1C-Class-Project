#include "polygon.h"

/****************************************************
* class Polygon - Derived Class
*****************************************************/

Polygon::Polygon(int    shapeId,
                 string shapeType,
                 QPoint coords,
                 QPen   pen,
                 QBrush brush)
               : Shape(shapeId,
                       shapeType,
                       coords,
                       pen,
                       brush)
{}

double Polygon::Perimeter() const
{
    double perimeter;

    perimeter = sqrt(pow((points[0][0] - points[1][0]), 2) + pow((points[0][1] - points[1][1]), 2) * points.size());

    return perimeter;
}

double Polygon::Area() const
{
    double apothem;

    apothem = (sqrt(pow((points[0][0] - points[1][0]), 2) + pow((points[0][1] - points[1][1]), 2))) / tan(180 / points.size());

    return (Perimeter() * apothem) / 2;
}

/****************************************************/

