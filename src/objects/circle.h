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

    int getR() const {return r;}    // Necessary for parser

    void Draw(QWidget* renderArea) override;

    double Perimeter() const override;
    double Area()      const override;

private:
    int r;

    // Disable Copy Operations
    //Circle(Circle& Circle) = delete;
};

#endif // CIRCLE_H

