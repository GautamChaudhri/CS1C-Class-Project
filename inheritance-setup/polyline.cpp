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

void Polyline::Draw()
{
    // This is an example but we need to change the coords to use and array or vector
    QPoint points[] = {QPoint(100, 100), QPoint(200, 50), QPoint(300, 150),
                       QPoint(250, 250), QPoint(150, 200)};

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawPolyline(points, pointCount);
    getPainter().restore();
}

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
