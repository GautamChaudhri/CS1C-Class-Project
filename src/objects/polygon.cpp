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
    parentItem->setText(0, QString::fromStdString(shapeType));

    for (int i = 0; i < 13; ++i)
    {
        childItems.push_back(new QTreeWidgetItem());
        parentItem->addChild(childItems[i]);
    }

        childItems[0]->setText(0, "Shape ID:");
        childItems[0]->setText(1, QString::number(getShapeId()));

        childItems[1]->setText(0, "Tracker ID:");
        childItems[1]->setText(1, QString::number(getTrackerId()));

        childItems[2]->setText(0, "Shape Type:");
        childItems[2]->setText(1, QString::fromStdString(getShapeType()));

        childItems[3]->setText(0, "X:");
        childItems[3]->setText(1, QString::number(pointsList[0].x()));
        childItems[3]->setFlags(getChildItems()[3]->flags() | Qt::ItemIsEditable);

        childItems[4]->setText(0, "Y:");
        childItems[4]->setText(1, QString::number(pointsList[0].y()));
        childItems[4]->setFlags(getChildItems()[4]->flags() | Qt::ItemIsEditable);

        childItems[5]->setText(0, "X2:");
        childItems[5]->setText(1, QString::number(pointsList[1].x()));
        childItems[5]->setFlags(getChildItems()[5]->flags() | Qt::ItemIsEditable);

        childItems[6]->setText(0, "Y2:");
        childItems[6]->setText(1, QString::number(pointsList[1].y()));
        childItems[6]->setFlags(getChildItems()[6]->flags() | Qt::ItemIsEditable);

        childItems[7]->setText(0, "X3:");
        childItems[7]->setText(1, QString::number(pointsList[2].x()));
        childItems[7]->setFlags(getChildItems()[7]->flags() | Qt::ItemIsEditable);

        childItems[8]->setText(0, "Y3:");
        childItems[8]->setText(1, QString::number(pointsList[2].y()));
        childItems[8]->setFlags(getChildItems()[8]->flags() | Qt::ItemIsEditable);

        childItems[9]->setText(0, "X4:");
        childItems[9]->setText(1, QString::number(pointsList[3].x()));
        childItems[9]->setFlags(getChildItems()[9]->flags() | Qt::ItemIsEditable);

        childItems[10]->setText(0, "Y4:");
        childItems[10]->setText(1, QString::number(pointsList[3].y()));
        childItems[10]->setFlags(getChildItems()[10]->flags() | Qt::ItemIsEditable);

        childItems[11]->setText(0, "Pen:");
        childItems[11]->setFlags(childItems[11]->flags() | Qt::ItemIsEditable);

        childItems[12]->setText(0, "Brush:");
        childItems[12]->setFlags(childItems[12]->flags() | Qt::ItemIsEditable);

        setShapeId(3);
}


Polygon::~Polygon() {}

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
