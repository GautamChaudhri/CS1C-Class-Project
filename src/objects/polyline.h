#ifndef POLYLINE_H
#define POLYLINE_H

#include "shape.h"

class Polyline : public Shape
{
public:
    Polyline(int    shapeId,
             string shapeType,
             QPoint coords,
             QPen   pen,
             QBrush brush,
             QPolygon pointsList);

    ~Polyline();

    void Draw(QWidget* renderArea) override;
    void Move(int x, int y) override;

    double Perimeter() const override;
    double Area() const override {return 0;}

    bool isPointInside(const QPoint& point) const override;

    QPolygon getPointsList() const;

private:
    QPolygon pointsList;
};

#endif // POLYLINE_H
