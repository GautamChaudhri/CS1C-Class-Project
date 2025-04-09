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
             QBrush brush);


    double Perimeter() const override;
    double Area()      const override;


private:
    std::vector < std::vector<int> > points; // temporary

    // Disable Copy Operations
    Polygon(Polygon& Polygon) = delete;
};
#endif // POLYGON_H
