#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape
{
public:
    Ellipse(string shapeType,
            QPoint coords,
            QPen   pen,
            QBrush brush,
            int    a,
            int    b);

    void Draw(QWidget* renderArea) override;

    double Perimeter() const override;
    double Area()      const override;

    bool isPointInside(const QPoint& point) const override;

    int getA() const;
    int getB() const;

private:
    int a; // rename a & b to semi major and minor axis?
    int b;
};

#endif // ELLIPSE_H
