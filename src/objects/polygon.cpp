#include "polygon.h"

/****************************************************
* derived class Polygon - Base Shape
*****************************************************/

Polygon::Polygon(string shapeType,
                 QPoint coords,
                 QPen   pen,
                 QBrush brush,
                 QPolygon pointsList)
               : Shape(shapeType,
                       coords,
                       pen,
                       brush),
                pointsList{pointsList}
{
    setShapeId(3);
    CreateParentItem();
    CreatePenChild();
    CreateBrushChild();
    CreatePointsChild(getPointsList().size());
}

void Polygon::Draw(QWidget* renderArea)
{
    if (!getPainter().isActive())
    {
        getPainter().begin(renderArea); // Ensure the painter is properly started
    }

    getPainter().save(); // Save current state

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawPolygon(pointsList);

    QRect boundingBox = pointsList.boundingRect();

    if (getSelected())
    {
        // Define a highlight pen for the bounding box
        QPen highlightPen(Qt::DashLine);
        highlightPen.setColor(Qt::red);
        getPainter().setPen(highlightPen);
        getPainter().setBrush(Qt::NoBrush);

        // Draw the bounding box around the polygon
        getPainter().drawRect(boundingBox);
    }

    //draws the shape id text
    QFont font;
    getPainter().setPen(Qt::black);
    font.setPointSize(10); // Sets the font size
    getPainter().setFont(font);
    getPainter().drawText(getX(), boundingBox.y(), QString("ID: " + QString::number(getShapeId())));

    getPainter().restore(); // Restore saved state

    getPainter().end(); // End the painter session
}


void Polygon::Move(int x, int y)
{
    int offsetX = x - getX(); // Calculate the change in x
    int offsetY = y - getY(); // Calculate the change in y

    // Update the position of the polygon
    setX(x);
    setY(y);

    // Adjust each point in pointsList based on the calculated deltas
    for (int i = 0; i < pointsList.size(); ++i)
    {
        pointsList[i].setX(pointsList[i].x() + offsetX);
        pointsList[i].setY(pointsList[i].y() + offsetY);
    }
}


double Polygon::Perimeter() const
{
    double perimeter;

    perimeter = sqrt(pow((pointsList[0].x() - pointsList[1].x()), 2) + pow((pointsList[0].y() - pointsList[1].y()), 2) * pointsList.size());

    return perimeter;
}

double Polygon::Area() const
{
    double apothem;

    apothem = (sqrt(pow((pointsList[0].x() - pointsList[1].x()), 2) + pow((pointsList[0].y() - pointsList[1].y()), 2))) / tan(180 / pointsList.size());

    return (Perimeter() * apothem) / 2;
}


bool Polygon::isPointInside(const QPoint& point) const
{
    return pointsList.containsPoint(point, Qt::OddEvenFill);
}


/************* ACCESSOR FUNCTIONS *************/
QPolygon Polygon::getPointsList() const { return pointsList; }
/**********************************************/

/************* MUTATOR FUNCTIONS *************/
void Polygon::setPointsList(const QPolygon& newPointsList) { pointsList = newPointsList; }
void Polygon::setX(int newX) { Shape::setX(newX); }
void Polygon::setY(int newY) { Shape::setY(newY); }
/**********************************************/
