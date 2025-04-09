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
                       brush) // todo: WE NEED SOME WAY OF STORING POINT COUNT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{}

void Polygon::Draw()
{

    // This is an example but we need to change the coords to use and array or vector
    QPoint points[] = {QPoint(100, 100), QPoint(200, 50), QPoint(300, 150),
                       QPoint(250, 250), QPoint(150, 200)};

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawPolygon(points, pointCount, Qt::OddEvenFill); // I am not sure what to do about the fill rule :/
    getPainter().restore();
}

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

