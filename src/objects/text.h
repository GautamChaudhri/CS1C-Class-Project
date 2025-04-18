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
         GlobalColor   textColor,
         AlignmentFlag textAlignment,
         QFont font,
         int length,
         int width);

    int           getLength() const;
    int           getWidth() const;
    QString       getTextString() const;
    GlobalColor   getTextColor() const;
    QFont         getFont() const;
    AlignmentFlag getTextAlignment() const;

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
