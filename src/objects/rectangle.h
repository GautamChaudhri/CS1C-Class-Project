#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(string shapeType,
              QPoint coords,
              QPen   pen,
              QBrush brush,
              int length,
              int width);


    void Draw(QWidget* renderArea) override;

    double Perimeter() const override;
    double Area()      const override;

    bool isPointInside(const QPoint& point) const override;

    int getLength() const;
    int getWidth()  const;

    void setLength(int newLength);
    void setWidth(int newWidth);
    void setX(int newX);
    void setY(int newY);

private:
    int length;
    int width;
};

#endif // RECTANGLE_H

