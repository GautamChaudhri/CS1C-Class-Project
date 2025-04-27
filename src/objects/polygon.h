#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"

class Polygon : public Shape
{
public:
    Polygon(string shapeType,
             QPoint coords,
             QPen   pen,
             QBrush brush,
             QPolygon pointsList);

    void Draw(QWidget* renderArea) override;
    void Move(int x, int y) override;

    double Perimeter() const override;
    double Area()      const override;

    bool isPointInside(const QPoint& point) const override;

    QPolygon getPointsList() const;

private:
    QPolygon pointsList;
};
#endif // POLYGON_H
