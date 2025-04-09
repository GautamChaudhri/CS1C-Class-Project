#include "circle.h"

/****************************************************
* class Circle - Derived Class
*****************************************************/

Circle::Circle(int         shapeId,
               std::string       shapeType,
               int          x,
               int          y,
               Qt::GlobalColor  penColor,
               int          penWidth,
               Qt::PenStyle     penStyle,
               Qt::PenCapStyle  penCapStyle,
               Qt::PenJoinStyle penJoinStyle,
               int          r)
    : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle,
            penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
    r{r}
{}

double Circle::Perimeter() const { return 2 * PI * r; }
double Circle::Area()      const { return PI * pow(r, 2); }

/****************************************************/
