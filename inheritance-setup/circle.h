#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape
{
public:
    Circle(int shapeId,
           std::string shapeType,
           int x,
           int y,
           Qt::GlobalColor penColor,
           int penWidth,
           Qt::PenStyle penStyle,
           Qt::PenCapStyle penCapStyle,
           Qt::PenJoinStyle penJoinStyle,
           int r);

    double Perimeter() const override;
    double Area()      const override;

private:
    int r;

    // Disable Copy Operations
    Circle(Circle& Circle) = delete;
};

#endif // CIRCLE_H
