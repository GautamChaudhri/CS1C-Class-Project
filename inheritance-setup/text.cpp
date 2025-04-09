#include "text.h"

/****************************************************
* class Text - Derived Class
*****************************************************/

Text::Text(int           shapeId,
           std::string        shapeType,
           int           x,
           int           y,
           std::string        textString,
           Qt::GlobalColor   textColor,
           Qt::AlignmentFlag textAlignment,
           int           textPointSize,
           std::string        textFontFamily,
           QFont::Style         textFontStyle,
           QFont::Weight        textFontWeight,
           int           length,
           int           width)
    : Shape(shapeId, shapeType, x, y, Qt::GlobalColor(), 0, Qt::PenStyle(), Qt::PenCapStyle(),
            Qt::PenJoinStyle(), Qt::GlobalColor(), Qt::BrushStyle()),
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

double Text::Perimeter() const { return (length * 2) + (width * 2); }
double Text::Area()      const { return length * width; }

/****************************************************/
