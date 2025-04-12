#ifndef POLYLINE_H
#define POLYLINE_H

#include "shape.h"
#include "renderarea.h"

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

    void Draw(RenderArea* renderArea) override;

    QPolygon getPointsList() { return pointsList; }

    double Perimeter() const override;
    double Area() const override {return 0;}

private:
    QPolygon pointsList;

    // Disable Copy Operations
    Polyline(Polyline& Polyline) = delete;
};

#endif // POLYLINE_H
