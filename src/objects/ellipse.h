#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape
{
public:
    Ellipse(int    shapeId,
            string shapeType,
            QPoint coords,
            QPen   pen,
            QBrush brush,
            int    a,
            int    b);

    void Draw(QWidget* renderArea) override;

    int getA() const;   // Necessary for parser
    int getB() const;

    double Perimeter() const override;
    double Area()      const override;

    bool isPointInside(const QPoint& point) const override
    {
        QRect rect(getX() - a, getY() - b, a*2, b*2);
        return rect.contains(point);
    }

private:
    int a;
    int b;
};

#endif // ELLIPSE_H
