#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"

class Square : public Shape
{
public:
    Square(int    shapeId,
           string shapeType,
           QPoint coords,
           QPen   pen,
           QBrush brush,
           int length);

    int getLength() const; // Necessary for parser

    void Draw(QWidget* renderArea) override;

    double Perimeter() const override;
    double Area()      const override;

    bool isPointInside(const QPoint& point) const override;

private:
    int length;
};

#endif // SQUARE_H
