#include "polygon.h"

/****************************************************
* class Polygon - Derived Class
*****************************************************/

Polygon::Polygon(int    shapeId,
                 string shapeType,
                 QPoint coords,
                 QPen   pen,
                 QBrush brush,
                 QPolygon pointsList)
               : Shape(shapeId,
                       shapeType,
                       coords,
                       pen,
                       brush),
                pointsList{pointsList}
{

}

Polygon::~Polygon() {}

void Polygon::Draw(QWidget* renderArea)
{
    getPainter().begin(renderArea);

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawPolygon(pointsList);

    getPainter().end();
}


double Polygon::Perimeter() const
{
    double perimeter;

    perimeter = sqrt(pow((pointsList[0].x() - pointsList[1].x()), 2) + pow((pointsList[0].y() - pointsList[1].y()), 2) * pointsList);

    return perimeter;
}

double Polygon::Area() const
{
    double apothem;

    apothem = (sqrt(pow((pointsList[0].x() - pointsList[1].x()), 2) + pow((pointsList[0].y() - pointsList[1].y()), 2))) / tan(180 / pointsList.size());

    return (Perimeter() * apothem) / 2;
}

/****************************************************/

