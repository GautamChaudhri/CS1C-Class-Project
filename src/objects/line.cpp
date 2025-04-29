#include "line.h"

/****************************************************
* derived class Line - Base Shape
*****************************************************/

Line::Line(string shapeType,
           QPoint coords,
           QPen   pen,
           QBrush brush,
           QPoint startPoint,
           QPoint endPoint)
        :  Shape (shapeType,
                  coords,
                  pen,
                  brush),
       startPoint{startPoint},
         endPoint{endPoint}
{
    setShapeId(1);
    CreateParentItem();
    AddPointsToParent(2);


    // parentItem->setText(0, QString::fromStdString(shapeType));

    // for (int i = 0; i < 3; ++i)
    // {
    //     childItems.push_back(new QTreeWidgetItem());
    //     parentItem->addChild(childItems[i + 5]);
    // }

    // childItems[5]->setText(0, "X2:");
    // childItems[5]->setText(1, QString::number(getX()));
    // childItems[5]->setFlags(getChildItems()[5]->flags() | Qt::ItemIsEditable);

    // childItems[6]->setText(0, "Y2:");
    // childItems[6]->setText(1, QString::number(getY()));
    // childItems[6]->setFlags(getChildItems()[6]->flags() | Qt::ItemIsEditable);

    // childItems[7]->setText(0, "Pen:");
    // childItems[7]->setFlags(childItems[7]->flags() | Qt::ItemIsEditable);
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


/************* MUTATOR FUNCTIONS *************/
void Line::setStartPoint(const QPoint& newStartPoint) { startPoint = newStartPoint; }
void Line::setEndPoint(const QPoint& newEndPoint) { endPoint = newEndPoint; }
void Line::setX(int newX) { Shape::setX(newX); }
void Line::setY(int newY) { Shape::setY(newY); }
/**********************************************/