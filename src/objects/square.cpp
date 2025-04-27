#include "square.h"

/****************************************************
* derived class Square - Base Shape
*****************************************************/

Square::Square(int    shapeId,
               string shapeType,
               QPoint coords,
               QPen   pen,
               QBrush brush,
               int length)
             : Shape(shapeId, shapeType, coords, pen, brush),
               length{length}
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

        childItems[5]->setText(0, "Length:");
        childItems[5]->setText(1, QString::number(getLength()));
        childItems[5]->setFlags(getChildItems()[5]->flags() | Qt::ItemIsEditable);

        childItems[6]->setText(0, "Pen:");
        childItems[6]->setFlags(childItems[6]->flags() | Qt::ItemIsEditable);

        childItems[7]->setText(0, "Brush:");
        childItems[7]->setFlags(childItems[7]->flags() | Qt::ItemIsEditable);
}

void Square::Draw(QWidget* renderArea)
{
    if (!getPainter().isActive())
    {
        getPainter().begin(renderArea); // Ensure the painter is properly started
    }

    getPainter().save(); // Save current state

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawRect(getX(),getY(), length, length);

    if (getSelected())
    {
        QPen highlightPen(Qt::DashLine);
        highlightPen.setColor(Qt::red);
        getPainter().setPen(highlightPen);
        getPainter().setBrush(Qt::NoBrush);
        getPainter().drawRect(getX(), getY(), length, length);
    }

    //draws the shape id text
    QFont font;
    getPainter().setPen(Qt::black);
    font.setPointSize(10); // Sets the font size
    getPainter().setFont(font);
    getPainter().drawText(getX(), getY(), QString("ID: " + QString::number(getShapeId())));

    getPainter().restore(); // Restore saved state

    getPainter().end(); // End the painter session
}


double Square::Perimeter() const { return length * 4; }
double Square::Area()      const { return pow(length, 2); }


bool Square::isPointInside(const QPoint& point) const
{
    QRect rect(getX(), getY(), length, length);
    return rect.contains(point);
}


/************* ACCESSOR FUNCTIONS *************/
int Square::getLength() const {return length;}
/**********************************************/

