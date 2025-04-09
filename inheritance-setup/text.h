#ifndef TEXT_H
#define TEXT_H

#include "shape.h"

class Text : public Shape
{
public:
    Text(int shapeId,
         std::string shapeType,
         int x,
         int y,
         std::string textString,
         Qt::GlobalColor textColor,
         Qt::AlignmentFlag textAlignment,
         int textPointSize,
         std::string textFontFamily,
         QFont::Style textFontStyle,
         QFont::Weight textFontWeight,
         int length,
         int width);

    double Perimeter() const override;
    double Area()      const override;

private:
    int length;
    int width;
    std::string textString;
    Qt::GlobalColor textColor;
    Qt::AlignmentFlag textAlignment;
    int textPointSize;
    std::string textFontFamily;
    QFont::Style textFontStyle;
    QFont::Weight textFontWeight;

    // Disable Copy Operations
    Text(Text& Text) = delete;
};

#endif // TEXT_H
