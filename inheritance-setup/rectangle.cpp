#include "rectangle.h"

/****************************************************
* class Rectangle - Derived Class
*****************************************************/

Rectangle::Rectangle(int    shapeId,
                     string shapeType,
                     QPoint coords,
                     QPen   pen,
                     QBrush brush,
                     int length,
                     int width)
                   : Shape(shapeId, shapeType, coords, pen, brush),
                    length{length},
                    width{width}
{}


double Rectangle::Perimeter() const { return (length * 2) + (width * 2); }
double Rectangle::Area()      const { return length * width; }

/****************************************************/
