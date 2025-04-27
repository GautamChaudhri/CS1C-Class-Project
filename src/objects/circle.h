#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape
{
public:
    Circle(string shapeType,
           QPoint coords,
           QPen   pen,
           QBrush brush,
           int r);

    void Draw(QWidget* renderArea) override;

    double Perimeter() const override;
    double Area()      const override;

    bool isPointInside(const QPoint& point) const override;

    int getR() const;

private:
    int r;
};

#endif // CIRCLE_H

