#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(int    shapeId,
              string shapeType,
              QPoint coords,
              QPen   pen,
              QBrush brush,
              int length,
              int width);

    void Draw(RenderArea* renderArea) override;

    double Perimeter() const override;
    double Area()      const override;

private:
    int length;
    int width;

    // Disable Copy Operations
    Rectangle(Rectangle& Rectangle) = delete;
};

#endif // RECTANGLE_H
