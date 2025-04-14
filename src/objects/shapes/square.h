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

    void Draw(QWidget* renderArea) override;

    double Perimeter() const override;
    double Area()      const override;

private:
    int length;

    // Disable Copy Operations
    //Square(Square& Square) = delete;
};

#endif // SQUARE_H
