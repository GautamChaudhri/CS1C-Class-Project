#include "square.h"

/****************************************************
* class Square - Derived Class
*****************************************************/

Square::Square(int    shapeId,
               string shapeType,
               QPoint coords,
               QPen   pen,
               QBrush brush,
               int length)
             : Shape(shapeId, shapeType, coords, pen, brush),
               length{length}
{}

void Square::Draw(QWidget* renderArea)
{
    getPainter().begin(renderArea);

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawRect(getX(),getY(), length, length);

    getPainter().end();
}

double Square::Perimeter() const { return length * 4; }
double Square::Area()      const { return pow(length, 2); }

/****************************************************/

