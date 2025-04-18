#include "line.h"

/****************************************************
* class Line - Derived Class
*****************************************************/

Line::Line(int    shapeId,
           string shapeType,
           QPoint coords,
           QPen   pen,
           QBrush brush,
           QPoint startPoint,
           QPoint endPoint)
        :  Shape (shapeId,
                  shapeType,
                  coords,
                  pen,
                  brush),
       startPoint{startPoint},
         endPoint{endPoint}
{}

void Line::Draw(QWidget* renderArea)
{
    getPainter().begin(renderArea);

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawLine(startPoint,endPoint);

    if (getSelected())
    {
        // Define a highlight pen for the bounding box
        QPen highlightPen(Qt::DashLine);
        highlightPen.setColor(Qt::red);
        getPainter().setPen(highlightPen);
        getPainter().setBrush(Qt::NoBrush);

        // Create and draw the bounding box
        const int margin = 5;
        int minX = std::min(startPoint.x(), endPoint.x()) - margin;
        int maxX = std::max(startPoint.x(), endPoint.x()) + margin;
        int minY = std::min(startPoint.y(), endPoint.y()) - margin;
        int maxY = std::max(startPoint.y(), endPoint.y()) + margin;

        QRect boundingBox(QPoint(minX, minY), QPoint(maxX, maxY));
        getPainter().drawRect(boundingBox);
    }

    getPainter().end();
}


double Line::Perimeter() const
{
    return sqrt(pow((startPoint.x() - endPoint.x()),2) + pow((startPoint.y() - endPoint.y()), 2));
}
