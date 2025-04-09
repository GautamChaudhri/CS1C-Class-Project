#include "polygon.h"

/****************************************************
* class Polygon - Derived Class
*****************************************************/

Polygon::Polygon(int shapeId,
                 std::string shapeType,
                 int x,
                 int y,
                 Qt::GlobalColor penColor,
                 int penWidth,
                 Qt::PenStyle penStyle,
                 Qt::PenCapStyle penCapStyle,
                 Qt::PenJoinStyle penJoinStyle,
                 Qt::GlobalColor brushColor,
                 Qt::BrushStyle brushStyle,
                 std::vector<int> points)
    : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle,
            penCapStyle, penJoinStyle, brushColor, brushStyle),
    points{points}
{}

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

