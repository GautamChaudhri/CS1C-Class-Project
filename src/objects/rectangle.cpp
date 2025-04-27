#include "rectangle.h"

/****************************************************
* derived class Rectangle - Base Shape
*****************************************************/

Rectangle::Rectangle(string shapeType,
                     QPoint coords,
                     QPen   pen,
                     QBrush brush,
                     int length,
                     int width)
                   : Shape(shapeType, coords, pen, brush),
                    length{length},
                    width{width}
{
    setShapeId(4);
}


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

    //draws the shape id text
    QFont font;
    getPainter().setPen(Qt::black);
    font.setPointSize(10); // Sets the font size
    getPainter().setFont(font);
    getPainter().drawText(getX(), getY(), QString("ID: " + QString::number(getShapeId())));

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
