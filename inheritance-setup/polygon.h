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
             QPoint *points,
             int    pointCount);

    void Draw() override;

    double Perimeter() const override;
    double Area()      const override;


private:
    QPoint * points; // pointer that will point to an array of QPoints
    int pointCount;

    // Disable Copy Operations
    Polygon(Polygon& Polygon) = delete;
};
#endif // POLYGON_H
