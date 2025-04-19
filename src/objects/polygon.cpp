#include "polygon.h"

/****************************************************
* class Polygon - Derived Class
*****************************************************/

Polygon::Polygon(int    shapeId,
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

Polygon::~Polygon() {}

bool Polygon::isPointInside(const QPoint& point) const
{
    return pointsList.containsPoint(point, Qt::OddEvenFill);
}

void Polygon::Move(int x, int y)
{
    int offsetX = x - getX(); // Calculate the change in x
    int offsetY = y - getY(); // Calculate the change in y

    // Update the position of the polygon
    setX(x);
    setY(y);

    // Adjust each point in pointsList based on the calculated deltas
    for (int i = 0; i < pointsList.size(); ++i)
    {
        pointsList[i].setX(pointsList[i].x() + offsetX);
        pointsList[i].setY(pointsList[i].y() + offsetY);
    }
}

void Polygon::Draw(QWidget* renderArea)
{
    if (!getPainter().isActive())
    {
        getPainter().begin(renderArea); // Ensure the painter is properly started
    }

    getPainter().save(); // Save current state

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawPolygon(pointsList);

    if (getSelected())
    {
        // Define a highlight pen for the bounding box
        QPen highlightPen(Qt::DashLine);
        highlightPen.setColor(Qt::red);
        getPainter().setPen(highlightPen);
        getPainter().setBrush(Qt::NoBrush);

        // Draw the bounding box around the polygon
        QRect boundingBox = pointsList.boundingRect();
        getPainter().drawRect(boundingBox);
    }

    getPainter().restore(); // Restore saved state

    getPainter().end(); // End the painter session
}

QPolygon Polygon::getPointsList() const
{
    return pointsList;
}

double Polygon::Perimeter() const
{
    double perimeter;

    perimeter = sqrt(pow((pointsList[0].x() - pointsList[1].x()), 2) + pow((pointsList[0].y() - pointsList[1].y()), 2) * pointsList.size());

    return perimeter;
}

double Polygon::Area() const
{
    double apothem;

    apothem = (sqrt(pow((pointsList[0].x() - pointsList[1].x()), 2) + pow((pointsList[0].y() - pointsList[1].y()), 2))) / tan(180 / pointsList.size());

    return (Perimeter() * apothem) / 2;
}

/****************************************************/

