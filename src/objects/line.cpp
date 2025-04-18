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

QPoint Line::getStartPoint() const
{
    return startPoint;
}

QPoint Line::getEndPoint() const
{
    return endPoint;
}

bool Line::isPointInside(const QPoint& point) const
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

void Line::Move(int x, int y)
{
    QPoint relativeStartPoint = startPoint - getPoints();
    QPoint relativeEndPoint = endPoint - getPoints();

    setX(x);
    setY(y);

    startPoint = getPoints() + relativeStartPoint;
    endPoint = getPoints() + relativeEndPoint;
}


void Line::Draw(QWidget* renderArea)
{
    if (!getPainter().isActive())
    {
        getPainter().begin(renderArea); // Ensure the painter is properly started
    }

    getPainter().save(); // Save current state

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

    getPainter().restore(); // Restore saved state

    getPainter().end(); // End the painter session
}

double Line::Perimeter() const
{
    return sqrt(pow((startPoint.x() - endPoint.x()),2) + pow((startPoint.y() - endPoint.y()), 2));
}
