#include "polyline.h"

/****************************************************
* class Polyline - Derived Class
*****************************************************/
Polyline::Polyline(int    shapeId,
                    string shapeType,
                    QPoint coords,
                    QPen   pen,
                    QBrush brush,
                   std::vector<int> points)
                : Shape(shapeId, shapeType, coords, pen, brush),
                points{points}
{}

double Polyline::Perimeter() const
{
    double perimeter;
    perimeter = 0;

    int vecSize;
    vecSize = points.size() - 1;

    for(int i = 0; i < vecSize; i ++)
    {
        perimeter += sqrt(pow((points[i][0] - points[i + 1][0]), 2) + pow((points[i][1] - points[i + 1][1]), 2));
    };

    return perimeter;
}

/****************************************************/
