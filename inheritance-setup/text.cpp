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
           int    textPointSize,
           string textFontFamily,
           QFont::Style  textFontStyle,
           QFont::Weight textFontWeight,
           int           length,
           int           width)
        : Shape(shapeId, shapeType, coords, QPen(), QBrush()),
            textString{textString},
            textColor{textColor},
            textAlignment{textAlignment},
            textPointSize{textPointSize},
            textFontFamily{textFontFamily},
            textFontStyle{textFontStyle},
            textFontWeight{textFontWeight},
            length{length},
            width{width}
{}

void Text::Draw()
{
    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawText(getX(),getY(), textString);
    getPainter().restore();
}

double Text::Perimeter() const { return (length * 2) + (width * 2); }
double Text::Area()      const { return length * width; }

/****************************************************/
