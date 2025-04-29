#ifndef LINE_H
#define LINE_H

#include "shape.h"

/****************************************************
* class Line - Derived Class
*****************************************************/
class Line : public Shape
{
public:

    Line(string shapeType,
         QPoint coords,
         QPen   pen,
         QBrush brush,
         QPoint startPoint,
         QPoint endPoint);

    void Draw(QWidget* renderArea) override;
    void Move(int x, int y) override;

    double Perimeter() const override;
    double Area() const override { return 0; }  // Need to implement this to instantiate Line

    bool isPointInside(const QPoint& point) const override;

    QPoint getStartPoint() const;
    QPoint getEndPoint()   const;

    void setStartPoint(const QPoint& newStartPoint);
    void setEndPoint(const QPoint& newEndPoint);
    void setX(int newX);
    void setY(int newY);
private:
    QPoint startPoint;
    QPoint endPoint;
    QPolygon pointsList[2];
};

#endif // LINE_H
