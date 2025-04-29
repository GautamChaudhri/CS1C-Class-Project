#include "polyline.h"

/****************************************************
* derived class Polyline - Base Shape
*****************************************************/
Polyline::Polyline(string shapeType,
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
    setShapeId(2);
    CreateParentItem();
    AddPointsToParent(getPointsList().size());


    // parentItem->setText(0, QString::fromStdString(shapeType));

    // for (int i = 0; i < 7; ++i)
    // {
    //     childItems.push_back(new QTreeWidgetItem());
    //     parentItem->addChild(childItems[i + 5]);
    // }

    // childItems[5]->setText(0, "X2:");
    // childItems[5]->setText(1, QString::number(pointsList[1].x()));
    // childItems[5]->setFlags(getChildItems()[5]->flags() | Qt::ItemIsEditable);

    // childItems[6]->setText(0, "Y2:");
    // childItems[6]->setText(1, QString::number(pointsList[1].y()));
    // childItems[6]->setFlags(getChildItems()[6]->flags() | Qt::ItemIsEditable);

    // childItems[7]->setText(0, "X3:");
    // childItems[7]->setText(1, QString::number(pointsList[2].x()));
    // childItems[7]->setFlags(getChildItems()[7]->flags() | Qt::ItemIsEditable);

    // childItems[8]->setText(0, "Y3:");
    // childItems[8]->setText(1, QString::number(pointsList[2].y()));
    // childItems[8]->setFlags(getChildItems()[8]->flags() | Qt::ItemIsEditable);

    // childItems[11]->setText(0, "Pen:");
    // childItems[11]->setFlags(childItems[11]->flags() | Qt::ItemIsEditable);
}

void Polyline::Draw(QWidget* renderArea)
{
    if (!getPainter().isActive())
    {
        getPainter().begin(renderArea); // Ensure the painter is properly started
    }

    getPainter().save(); // Save current state

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawPolyline(pointsList);

    QRect boundingBox = pointsList.boundingRect();

    if (getSelected()) {
        // Define a highlight pen for the bounding box
        QPen highlightPen(Qt::DashLine);
        highlightPen.setColor(Qt::red);
        getPainter().setPen(highlightPen);
        getPainter().setBrush(Qt::NoBrush);

        // Draw the bounding box around the polyline
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


void Polyline::Move(int x, int y)
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


bool Polyline::isPointInside(const QPoint& point) const
{
    return pointsList.containsPoint(point, Qt::OddEvenFill);
}


double Polyline::Perimeter() const
{
    double perimeter;
    perimeter = 0;

    int size;
    size = pointsList.size() - 1;

    for(int i = 0; i < size; i ++)
    {
        perimeter += sqrt(pow((pointsList[i].x() - pointsList[i + 1].x()), 2) + pow((pointsList[i].y() - pointsList[i + 1].y()), 2));
    };

    return perimeter;
}


/************* ACCESSOR FUNCTIONS *************/
QPolygon Polyline::getPointsList() const { return pointsList; }
/**********************************************/

/************* MUTATOR FUNCTIONS *************/
void Polyline::setPointsList(const QPolygon& newPointsList) { pointsList = newPointsList; }
void Polyline::setX(int newX) { Shape::setX(newX); }
void Polyline::setY(int newY) { Shape::setY(newY); }
/**********************************************/