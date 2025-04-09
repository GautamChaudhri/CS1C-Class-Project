#ifndef LINE_H
#define LINE_H

#include "shape.h"

/****************************************************
* class Line - Derived Class
*****************************************************/
class Line : public Shape
{
public:

    Line(     int         shapeId,
         std::string      shapeType,
         int          x,
         int          y,
         Qt::GlobalColor  penColor,
         int          penWidth,
         Qt::PenStyle     penStyle,
         Qt::PenCapStyle  penCapStyle,
         Qt::PenJoinStyle penJoinStyle,
         int          x1,
         int          y1,
         int          x2,
         int          y2);


    double Perimeter() const override;

private:
    int x1;
    int y1;
    int x2;
    int y2;

    // Disable Copy Operations
    Line(Line& Line) = delete;
};

#endif // LINE_H
