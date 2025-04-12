#include "polyline.h"

/****************************************************
* class Polyline - Derived Class
*****************************************************/
Polyline::Polyline(int    shapeId,
                    string shapeType,
                    QPoint coords,
                    QPen   pen,
                    QBrush brush,
                    QPoint *points,
                    int    pointCount)
                : Shape(shapeId,
                        shapeType,
                        coords,
                        pen,
                        brush),
                    points{points},
                    pointCount{pointCount}
{}

Polyline::~Polyline() { delete points; }

void Polyline::Draw()
{
    getPainter().setPen(getPen());
    getPainter().drawPolyline(points, pointCount);
    getPainter().restore();
}

double Polyline::Perimeter() const
{
    double perimeter;
    perimeter = 0;

    int size;
    size = pointCount - 1;

    for(int i = 0; i < size; i ++)
    {
        perimeter += sqrt(pow((points[i].x() - points[i + 1].x()), 2) + pow((points[i].y() - points[i + 1].y()), 2));
    };

    return perimeter;
}

/****************************************************/
