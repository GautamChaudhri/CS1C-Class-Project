#ifndef LINE_H
#define LINE_H

#include "shape.h"

/****************************************************
* class Line - Derived Class
*****************************************************/
class Line : public Shape
{
public:

    Line(int    shapeId,
          string shapeType,
          QPoint coords,
          QPen   pen,
          QBrush brush,
          QPoint startPoint,
         QPoint endPoint);

    void Draw(QWidget* renderArea) override;

    double Perimeter() const override;

private:
    QPoint startPoint;
    QPoint endPoint;

    // Disable Copy Operations
    //Line(Line& Line) = delete;
};

#endif // LINE_H
