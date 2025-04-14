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

    void Draw(QWidget* renderArea) override;

    double Perimeter() const override;
    double Area()      const override;

private:
    int length;
    int width;

    QString       textString;
    GlobalColor   textColor;
    QFont         font;
    AlignmentFlag textAlignment;

    // Disable Copy Operations
    //Text(Text& Text) = delete;
};

#endif // TEXT_H
