#include "circle.h"

/****************************************************
* class Circle - Derived Class
*****************************************************/

Circle::Circle(int    shapeId,
               string shapeType,
               QPoint coords,
               QPen   pen,
               QBrush brush,
               int    r)
       : Shape(shapeId,
               shapeType,
               coords,
               pen,
               brush),
               r{r}
{}

void Circle::Draw(QWidget* renderArea)
{
    getPainter().begin(renderArea);

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawEllipse(getPoints(), r, r);

    getPainter().end();
}

int Circle::getR() const { return r; }

double Circle::Perimeter() const { return 2 * PI * r; }
double Circle::Area()      const { return PI * pow(r, 2); }

/****************************************************/
