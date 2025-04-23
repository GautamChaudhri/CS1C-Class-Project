#include "rectangle.h"

/****************************************************
* derived class Rectangle - Base Shape
*****************************************************/

Rectangle::Rectangle(int    shapeId,
                     string shapeType,
                     QPoint coords,
                     QPen   pen,
                     QBrush brush,
                     int length,
                     int width)
    : Shape(shapeId, shapeType, coords, pen, brush),
    length{length},
    width{width}
{}


void Rectangle::Draw(QWidget* renderArea)
{
    if (!getPainter().isActive())
    {
        getPainter().begin(renderArea); // Ensure the painter is properly started
    }

    getPainter().save(); // Save current state

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawRect(getX(),getY(), length, width);

    if (getSelected())
    {
        QPen highlightPen(Qt::DashLine);
        highlightPen.setColor(Qt::red);
        getPainter().setPen(highlightPen);
        getPainter().setBrush(Qt::NoBrush);
        getPainter().drawRect(getX(), getY(), length, width);
    }

    getPainter().restore(); // Restore saved state

    getPainter().end(); // End the painter session
}


double Rectangle::Perimeter() const { return (length * 2) + (width * 2); }
double Rectangle::Area()      const { return length * width; }


bool Rectangle::isPointInside(const QPoint& point) const
{
    QRect rect(getX(), getY(), length, width);
    return rect.contains(point);
}


/************* ACCESSOR FUNCTIONS *************/
int Rectangle::getLength() const { return length; }
int Rectangle::getWidth()  const { return width; }
/**********************************************/
