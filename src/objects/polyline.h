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
             QPoint *points,
             int    pointCount);

    ~Polyline();

    void Draw() override;

    double Perimeter() const override;
    double Area() const override { return 0; }  // Need to implement this to instantiate Line

private:
    QPoint * points; // pointer that will point to an array of QPoints
    int pointCount;

    // Disable Copy Operations
    Polyline(Polyline& Polyline) = delete;
};

#endif // POLYLINE_H
