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

double Circle::Perimeter() const { return 2 * PI * r; }
double Circle::Area()      const { return PI * pow(r, 2); }

/****************************************************/
