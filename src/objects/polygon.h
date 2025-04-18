#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"

class Polygon : public Shape
{
public:
    Polygon(int    shapeId,
             string shapeType,
             QPoint coords,
             QPen   pen,
             QBrush brush,
             QPolygon pointsList);

    ~Polygon();

    QPolygon getPointsList() const { return pointsList; } // Necessary for parser

    void Draw(QWidget* renderArea) override;

    double Perimeter() const override;
    double Area()      const override;

    bool isPointInside(const QPoint& point) const override;

private:
    QPolygon pointsList;
};
#endif // POLYGON_H
