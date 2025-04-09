#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(int shapeId,
              std::string shapeType,
              int x,
              int y,
              Qt::GlobalColor penColor,
              int penWidth,
              Qt::PenStyle penStyle,
              Qt::PenCapStyle penCapStyle,
              Qt::PenJoinStyle penJoinStyle,
              int length,
              int width);

    double Perimeter() const override;
    double Area()      const override;

private:
    int length;
    int width;

    // Disable Copy Operations
    Rectangle(Rectangle& Rectangle) = delete;
};

#endif // RECTANGLE_H
