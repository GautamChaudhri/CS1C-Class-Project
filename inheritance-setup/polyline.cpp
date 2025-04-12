#include "polyline.h"

/****************************************************
* class Polyline - Derived Class
*****************************************************/
Polyline::Polyline(int    shapeId,
                    string shapeType,
                    QPoint coords,
                    QPen   pen,
                    QBrush brush,
                    QPolygon pointsList)
                : Shape(shapeId,
                        shapeType,
                        coords,
                        pen,
                        brush),
                    pointsList{pointsList}
{}

Polyline::~Polyline() {}

void Polyline::Draw(RenderArea* renderArea)
{
    painter.begin(renderArea);

    painter.setPen(getPen());
    painter.setBrush(getBrush());
    painter.drawPolyline(pointsList);

    painter.end();
}

double Polyline::Perimeter() const
{
    double perimeter;
    perimeter = 0;

    int size;
    size =  0; //pointCount - 1;

    for(int i = 0; i < size; i ++)
    {
        perimeter += sqrt(pow((pointsList[i].x() - pointsList[i + 1].x()), 2) + pow((pointsList[i].y() - pointsList[i + 1].y()), 2));
    };

    return perimeter;
}

/****************************************************/
