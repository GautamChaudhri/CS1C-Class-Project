#include "circle.h"

/****************************************************
* derived class Circle - Base Shape
*****************************************************/

Circle::Circle(string shapeType,
               QPoint coords,
               QPen   pen,
               QBrush brush,
               int    r)
       : Shape(shapeType,
               coords,
               pen,
               brush),
               r{r}
{
    parentItem->setText(0, QString::fromStdString(shapeType));

    for (int i = 0; i < 8; ++i)
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
        childItems[3]->setText(1, QString::number(getX()));
        childItems[3]->setFlags(getChildItems()[3]->flags() | Qt::ItemIsEditable);

        childItems[4]->setText(0, "Y:");
        childItems[4]->setText(1, QString::number(getY()));
        childItems[4]->setFlags(getChildItems()[4]->flags() | Qt::ItemIsEditable);

        childItems[5]->setText(0, "Radius:");
        childItems[5]->setText(1, QString::number(r));
        childItems[5]->setFlags(getChildItems()[5]->flags() | Qt::ItemIsEditable);

        childItems[6]->setText(0, "Pen:");
        childItems[6]->setFlags(childItems[6]->flags() | Qt::ItemIsEditable);

        childItems[7]->setText(0, "Brush:");
        childItems[7]->setFlags(childItems[7]->flags() | Qt::ItemIsEditable);
    setShapeId(7);

    getChildItems().push_back(new QTreeWidgetItem());
    getParentItem()->addChild(getChildItems()[5]);
    getChildItems()[5]->setText(0, "Radius:");
}


void Circle::Draw(QWidget* renderArea)
{
    if (!getPainter().isActive())
    {
        getPainter().begin(renderArea); // Ensure the painter is properly started
    }

    getPainter().save(); // Save current state

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawEllipse(getPoints(), r, r);

    if (getSelected())
    {
        QPen highlightPen(Qt::DashLine);
        highlightPen.setColor(Qt::red);
        getPainter().setPen(highlightPen);
        getPainter().setBrush(Qt::NoBrush);
        getPainter().drawRect(getX() - r, getY() - r, r * 2, r * 2);
    }

    //draws the shape id text
    QFont font;
    getPainter().setPen(Qt::black);
    font.setPointSize(10); // Sets the font size
    getPainter().setFont(font);
    getPainter().drawText(getX() - r, getY() - r, QString("ID: " + QString::number(getShapeId())));

    getPainter().restore(); // Restore saved state

    getPainter().end(); // End the painter session
}

double Circle::Perimeter() const { return 2 * PI * r; }
double Circle::Area()      const { return PI * pow(r, 2); }

bool Circle::isPointInside(const QPoint& point) const
{
    QRect rect(getX() - r, getY() - r, r*2, r*2);
    return rect.contains(point);
}

/************* ACCESSOR FUNCTIONS *************/
int Circle::getR() const { return r; }
/**********************************************/
