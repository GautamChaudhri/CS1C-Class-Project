#ifndef TEXT_H
#define TEXT_H

#include "shape.h"

class Text : public Shape
{
public:
    Text(int    shapeId,
         string shapeType,
         QPoint coords,
         string textString,
         Qt::GlobalColor   textColor,
         Qt::AlignmentFlag textAlignment,
         int    textPointSize,
         string textFontFamily,
         QFont::Style  textFontStyle,
         QFont::Weight textFontWeight,
         int           length,
         int           width);

    double Perimeter() const override;
    double Area()      const override;

private:
    int length;
    int width;

    string        textString;
    GlobalColor   textColor;
    AlignmentFlag textAlignment;
    int           textPointSize;
    string        textFontFamily;
    QFont::Style  textFontStyle;
    QFont::Weight textFontWeight;

    // Disable Copy Operations
    Text(Text& Text) = delete;
};

#endif // TEXT_H
