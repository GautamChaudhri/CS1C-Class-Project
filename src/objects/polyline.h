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

    QPolygon getPointsList() const { return pointsList; } // Necessary for parser

    void Draw(QWidget* renderArea) override;

    double Perimeter() const override;
    double Area() const override {return 0;}

private:
    QPolygon pointsList;
};

#endif // POLYLINE_H
