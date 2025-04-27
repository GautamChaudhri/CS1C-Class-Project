#include "line.h"

/****************************************************
* derived class Line - Base Shape
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
    if (!getPainter().isActive())
    {
        getPainter().begin(renderArea); // Ensure the painter is properly started
    }

    getPainter().save(); // Save current state

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawLine(startPoint,endPoint);

    // Create and draw the bounding box
    int minX = std::min(startPoint.x(), endPoint.x());
    int maxX = std::max(startPoint.x(), endPoint.x());
    int minY = std::min(startPoint.y(), endPoint.y());
    int maxY = std::max(startPoint.y(), endPoint.y());

    QRect boundingBox(QPoint(minX, minY), QPoint(maxX, maxY));

    if (getSelected())
    {
        // Define a highlight pen for the bounding box
        QPen highlightPen(Qt::DashLine);
        highlightPen.setColor(Qt::red);
        getPainter().setPen(highlightPen);
        getPainter().setBrush(Qt::NoBrush);

        getPainter().drawRect(boundingBox);
    }

    //draws the shape id text
    QFont font;

    getPainter().setPen(Qt::black);
    font.setPointSize(10); // Sets the font size
    getPainter().setFont(font);
    getPainter().drawText(boundingBox.x(), boundingBox.y(), QString("ID: " + QString::number(getShapeId())));

    getPainter().restore(); // Restore saved state

    getPainter().end(); // End the painter session
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


double Line::Perimeter() const
{
    return sqrt(pow((startPoint.x() - endPoint.x()),2) + pow((startPoint.y() - endPoint.y()), 2));
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


/************* ACCESSOR FUNCTIONS *************/
QPoint Line::getStartPoint() const { return startPoint; }
QPoint Line::getEndPoint()   const { return endPoint; }
/**********************************************/


