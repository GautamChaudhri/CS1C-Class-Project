#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape
{
public:
    Ellipse(int    shapeId,
            string shapeType,
            QPoint coords,
            QPen   pen,
            QBrush brush,
            int    a,
            int    b);

    double Perimeter() const override;
    double Area()      const override;

private:
    int a;
    int b;

    // Disable Copy Operations
    Ellipse(Ellipse& Ellipse) = delete;
};

#endif // ELLIPSE_H
