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

bool Polyline::isPointInside(const QPoint& point) const
{
    return pointsList.containsPoint(point, Qt::OddEvenFill);
}

void Polyline::Draw(QWidget* renderArea)
{
    getPainter().begin(renderArea);

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawPolyline(pointsList);

    if (getSelected()) {
        // Define a highlight pen for the bounding box
        QPen highlightPen(Qt::DashLine);
        highlightPen.setColor(Qt::red);
        getPainter().setPen(highlightPen);
        getPainter().setBrush(Qt::NoBrush);

        // Draw the bounding box around the polyline
        QRect boundingBox = pointsList.boundingRect().adjusted(-5, -5, 5, 5); // With margin
        getPainter().drawRect(boundingBox);
    }

    getPainter().end();
}

double Polyline::Perimeter() const
{
    double perimeter;
    perimeter = 0;

    int size;
    size = pointsList.size() - 1;

    for(int i = 0; i < size; i ++)
    {
        perimeter += sqrt(pow((pointsList[i].x() - pointsList[i + 1].x()), 2) + pow((pointsList[i].y() - pointsList[i + 1].y()), 2));
    };

    return perimeter;
}

/****************************************************/
