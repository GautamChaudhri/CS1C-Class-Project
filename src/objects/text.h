#ifndef TEXT_H
#define TEXT_H

#include "shape.h"

class Text : public Shape
{
public:
    Text(int    shapeId,
         string shapeType,
         QPoint coords,
         QString textString,
         Qt::GlobalColor   textColor,
         Qt::AlignmentFlag textAlignment,
         QFont font,
         int           length,
         int           width);

    int getLength() const {return length;}  // Necessary for parser
    int getWidth() const {return width;}
    QString getTextString() const {return textString;}
    GlobalColor getTextColor() const {return textColor;}
    QFont getFont() const { return font; }
    AlignmentFlag getTextAlignment() const {return textAlignment;}

    void Draw(QWidget* renderArea) override;

    double Perimeter() const override;
    double Area()      const override;

    bool isPointInside(const QPoint& point) const override;

private:
    int length;
    int width;

    QString       textString;
    GlobalColor   textColor;
    QFont         font;
    AlignmentFlag textAlignment;
};

#endif // TEXT_H
