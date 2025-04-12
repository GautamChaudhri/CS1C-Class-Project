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
    perimeter = 0;

    //perimeter = sqrt(pow((points[0].x() - points[1].x()), 2) + pow((points[0].y() - points[1].y()), 2) * pointCount);

    return perimeter;
}

double Polygon::Area() const
{
    double apothem;

    //apothem = (sqrt(pow((points[0].x() - points[1].x()), 2) + pow((points[0].y() - points[1].y()), 2))) / tan(180 / pointCount);

    return 0; //(Perimeter() * apothem) / 2;
}

/****************************************************/

