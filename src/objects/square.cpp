#include "square.h"

/****************************************************
* derived class Square - Base Shape
*****************************************************/

Square::Square(int    trackerId,
               string shapeType,
               QPoint coords,
               QPen   pen,
               QBrush brush,
               int length)
             : Shape(trackerId, shapeType, coords, pen, brush),
               length{length}
{}


void Square::Draw(QWidget* renderArea)
{
    if (!getPainter().isActive())
    {
        getPainter().begin(renderArea); // Ensure the painter is properly started
    }

    getPainter().save(); // Save current state

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawRect(getX(),getY(), length, length);

    if (getSelected())
    {
        QPen highlightPen(Qt::DashLine);
        highlightPen.setColor(Qt::red);
        getPainter().setPen(highlightPen);
        getPainter().setBrush(Qt::NoBrush);
        getPainter().drawRect(getX(), getY(), length, length);
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


double Square::Perimeter() const { return length * 4; }
double Square::Area()      const { return pow(length, 2); }


bool Square::isPointInside(const QPoint& point) const
{
    QRect rect(getX(), getY(), length, length);
    return rect.contains(point);
}


/************* ACCESSOR FUNCTIONS *************/
int Square::getLength() const {return length;}
/**********************************************/

