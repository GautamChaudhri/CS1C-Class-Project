#ifndef LINE_H
#define LINE_H

#include "shape.h"

/****************************************************
* class Line - Derived Class
*****************************************************/
class Line : public Shape
{
public:

    Line(int    shapeId,
          string shapeType,
          QPoint coords,
          QPen   pen,
          QBrush brush,
          QPoint startPoint,
         QPoint endPoint);

    QPoint getStartPoint() const {return startPoint;}   // Necessary for parser
    QPoint getEndPoint() const {return endPoint;}

    void Draw(QWidget* renderArea) override;

    double Perimeter() const override;
    double Area() const override { return 0; }  // Need to implement this to instantiate Line

    bool isPointInside(const QPoint& point) const override
    {
        // Define a margin for the bounding box (e.g., 5 pixels)
        const int margin = 5;

        // Create a bounding rectangle around the line
        int minX = std::min(startPoint.x(), endPoint.x()) - margin;
        int maxX = std::max(startPoint.x(), endPoint.x()) + margin;
        int minY = std::min(startPoint.y(), endPoint.y()) - margin;
        int maxY = std::max(startPoint.y(), endPoint.y()) + margin;

        QRect boundingBox(QPoint(minX, minY), QPoint(maxX, maxY));

        // Check if the point is inside the bounding box
        return boundingBox.contains(point);
    }

private:
    QPoint startPoint;
    QPoint endPoint;
};

#endif // LINE_H
