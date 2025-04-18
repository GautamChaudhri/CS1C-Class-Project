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

bool Circle::isPointInside(const QPoint& point) const
{
    QRect rect(getX() - r, getY() - r, r*2, r*2);
    return rect.contains(point);
}

void Circle::Draw(QWidget* renderArea)
{
    if (!getPainter().isActive())
    {
        getPainter().begin(renderArea); // Ensure the painter is properly started
    }

    getPainter().save(); // Save current state

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawEllipse(getPoints(), r, r);

    if (getSelected())
    {
        QPen highlightPen(Qt::DashLine);
        highlightPen.setColor(Qt::red);
        getPainter().setPen(highlightPen);
        getPainter().setBrush(Qt::NoBrush);
        getPainter().drawRect(getX() - r, getY() - r, r * 2, r * 2);
    }

    getPainter().restore(); // Restore saved state

    getPainter().end(); // End the painter session
}

int Circle::getR() const { return r; }

double Circle::Perimeter() const { return 2 * PI * r; }
double Circle::Area()      const { return PI * pow(r, 2); }

/****************************************************/
