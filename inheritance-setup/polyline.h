#ifndef POLYLINE_H
#define POLYLINE_H

#include "shape.h"

class Polyline : public Shape
{
public:
    Polyline(int          shapeId,
           std::string       shapeType,
           int          x,
           int          y,
           Qt::GlobalColor  penColor,
           int          penWidth,
           Qt::PenStyle     penStyle,
           Qt::PenCapStyle  penCapStyle,
           Qt::PenJoinStyle penJoinStyle,
             std::vector<int>  points);

    double Perimeter() const override;

private:
    std::vector < std::vector<int> > points;

    // Disable Copy Operations
    Polyline(Polyline& Polyline) = delete;
};

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

#endif // POLYLINE_H
