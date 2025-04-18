#include "text.h"

/****************************************************
* class Text - Derived Class
*****************************************************/

Text::Text(int    shapeId,
           string shapeType,
           QPoint coords,
           QString textString,
           Qt::GlobalColor   textColor,
           Qt::AlignmentFlag textAlignment,
           QFont             font,
           int           length,
           int           width)
        : Shape(shapeId, shapeType, coords, QPen(), QBrush()),
            textString{textString},
            textColor{textColor},
            textAlignment{textAlignment},
            font{font},
            length{length},
            width{width}
{}

bool Text::isPointInside(const QPoint& point) const
{
    QRect rect(getX(), getY(), length, width);
    return rect.contains(point);
}

void Text::Draw(QWidget* renderArea)
{
    getPainter().begin(renderArea);

    getPainter().setPen(textColor);
    getPainter().setFont(font);
    getPainter().drawText(QRect(getX(),getY(),length,width),textAlignment, textString);
    getPainter().restore();

    if (getSelected())
    {
        QPen highlightPen(Qt::DashLine);
        highlightPen.setColor(Qt::red);
        getPainter().setPen(highlightPen);
        getPainter().setBrush(Qt::NoBrush);
        getPainter().drawRect(getX(), getY(), length, width);
    }

    getPainter().end();
}

double Text::Perimeter() const { return (length * 2) + (width * 2); }
double Text::Area()      const { return length * width; }

/****************************************************/
