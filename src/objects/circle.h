#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape
{
public:
    Circle(int    shapeId,
           string shapeType,
           QPoint coords,
           QPen   pen,
           QBrush brush,
           int r);

    void Draw(QWidget* renderArea) override;

    int getR() const; // Necessary for parser

    double Perimeter() const override;
    double Area()      const override;

    bool isPointInside(const QPoint& point) const override
    {
        QRect rect(getX() - r, getY() - r, r*2, r*2);
        return rect.contains(point);
    }

private:
    int r;
};

#endif // CIRCLE_H

