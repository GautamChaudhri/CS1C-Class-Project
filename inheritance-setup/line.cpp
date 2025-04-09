#include "line.h"

/****************************************************
* class Line - Derived Class
*****************************************************/

Line::Line(int    shapeId,
           string shapeType,
           QPoint coords,
           QPen   pen,
           QBrush brush,
           QPoint startPoint,
           QPoint endPoint)
        :  Shape (shapeId,
                  shapeType,
                  coords,
                  pen,
                  brush),
       startPoint{startPoint},
         endPoint{endPoint}
{

}

double Line::Perimeter() const
{
    return sqrt(pow((x1 - x2),2) + pow((y1 - y2), 2));
}
