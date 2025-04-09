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
             std::vector<int>  points);

    double Perimeter() const override;

private:
    std::vector < std::vector<int> > points;

    // Disable Copy Operations
    Polyline(Polyline& Polyline) = delete;
};

#endif // POLYLINE_H
