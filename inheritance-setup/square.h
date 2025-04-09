#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"

class Square : public Shape
{
public:
    Square(int shapeId,
           std::string shapeType,
           int x,
           int y,
           Qt::GlobalColor penColor,
           int penWidth,
           Qt::PenStyle penStyle,
           Qt::PenCapStyle penCapStyle,
           Qt::PenJoinStyle penJoinStyle,
           int length);

    double Perimeter() const override;
    double Area()      const override;

private:
    int length;

    // Disable Copy Operations
    Square(Square& Square) = delete;
};

#endif // SQUARE_H
