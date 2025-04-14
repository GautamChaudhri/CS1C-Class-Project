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

void Text::Draw()
{  
    getPainter().setPen(textColor);
    getPainter().setFont(font);
    getPainter().drawText(QRect(getX(),getY(),length,width),textAlignment, textString);
    getPainter().restore();
}

double Text::Perimeter() const { return (length * 2) + (width * 2); }
double Text::Area()      const { return length * width; }

/****************************************************/
