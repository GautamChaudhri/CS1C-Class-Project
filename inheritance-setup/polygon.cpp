#include "polygon.h"

/****************************************************
* class Polygon - Derived Class
*****************************************************/

Polygon::Polygon(int    shapeId,
                 string shapeType,
                 QPoint coords,
                 QPen   pen,
                 QBrush brush,
                 QPoint *points,
                 int    pointCount)
               : Shape(shapeId,
                       shapeType,
                       coords,
                       pen,
                       brush),
                points{points},
                pointCount{pointCount}
{}

void Polygon::Draw()
{
    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawPolygon(points, pointCount);
    getPainter().restore();
}


double Polygon::Perimeter() const
{
    double perimeter;

    perimeter = sqrt(pow((points[0].x() - points[1].x()), 2) + pow((points[0].y() - points[1].y()), 2) * pointCount);

    return perimeter;
}

double Polygon::Area() const
{
    double apothem;

    apothem = (sqrt(pow((points[0].x() - points[1].x()), 2) + pow((points[0].y() - points[1].y()), 2))) / tan(180 / pointCount);

    return (Perimeter() * apothem) / 2;
}

/****************************************************/

