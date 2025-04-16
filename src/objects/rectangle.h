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


    int getLength() const {return length;}  // Necessary for parser
    int getWidth() const {return width;}

    void Draw(QWidget* renderArea) override;

    double Perimeter() const override;
    double Area()      const override;

private:
    int length;
    int width;
};

#endif // RECTANGLE_H

