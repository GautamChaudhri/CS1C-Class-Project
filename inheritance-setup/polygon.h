#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"

class Polygon : public Shape
{
public:
    Polygon(int shapeId,
            std::string shapeType,
            int x,
            int y,
            Qt::GlobalColor penColor,
            int penWidth,
            Qt::PenStyle penStyle,
            Qt::PenCapStyle penCapStyle,
            Qt::PenJoinStyle penJoinStyle,
            Qt::GlobalColor brushColor,
            Qt::BrushStyle brushStyle,
            std::vector<int> points);


    double Perimeter() const override;
    double Area()      const override;


private:
    std::vector < std::vector<int> > points;

    // Disable Copy Operations
    Polygon(Polygon& Polygon) = delete;
};
#endif // POLYGON_H
