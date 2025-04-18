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

    QPoint getStartPoint() const {return startPoint;}   // Necessary for parser
    QPoint getEndPoint() const {return endPoint;}

    void Move(int x, int y) override;

    void Draw(QWidget* renderArea) override;

    double Perimeter() const override;
    double Area() const override { return 0; }  // Need to implement this to instantiate Line

    bool isPointInside(const QPoint& point) const override;

private:
    QPoint startPoint;
    QPoint endPoint;
};

#endif // LINE_H
