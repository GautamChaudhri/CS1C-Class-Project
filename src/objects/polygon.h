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

    void Draw(QWidget* renderArea) override;

    QPolygon getPointsList() { return pointsList; }


    double Perimeter() const override;
    double Area()      const override;


private:
    QPolygon pointsList;

    // Disable Copy Operations
    //Polygon(Polygon& Polygon) = delete;
};
#endif // POLYGON_H
