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

    if (getSelected())
    {
        // Define a highlight pen for the bounding box
        QPen highlightPen(Qt::DashLine);
        highlightPen.setColor(Qt::red);
        getPainter().setPen(highlightPen);
        getPainter().setBrush(Qt::NoBrush);

        // Draw the bounding box around the polygon
        QRect boundingBox = pointsList.boundingRect();
        getPainter().drawRect(boundingBox);
    }

    getPainter().end();
}


double Polygon::Perimeter() const
{
    double perimeter;

    perimeter = sqrt(pow((pointsList[0].x() - pointsList[1].x()), 2) + pow((pointsList[0].y() - pointsList[1].y()), 2) * pointsList.size());

    return perimeter;
}

double Polygon::Area() const
{
    double apothem;

    apothem = (sqrt(pow((pointsList[0].x() - pointsList[1].x()), 2) + pow((pointsList[0].y() - pointsList[1].y()), 2))) / tan(180 / pointsList.size());

    return (Perimeter() * apothem) / 2;
}

/****************************************************/

