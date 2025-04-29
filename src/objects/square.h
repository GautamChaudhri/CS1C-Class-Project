#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"

class Square : public Shape
{
public:
    Square(string shapeType,
           QPoint coords,
           QPen   pen,
           QBrush brush,
           int length);


    void Draw(QWidget* renderArea) override;

    double Perimeter() const override;
    double Area()      const override;

    bool isPointInside(const QPoint& point) const override;

    int getLength() const;

    void setLength(int newLength);
    void setX(int newX);
    void setY(int newY);

private:
    int length;
};

#endif // SQUARE_H
