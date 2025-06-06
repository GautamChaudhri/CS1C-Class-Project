#include "rectangle.h"

/****************************************************
* derived class Rectangle - Base Shape
*****************************************************/

Rectangle::Rectangle(string shapeType,
                     QPoint coords,
                     QPen   pen,
                     QBrush brush,
                     int length,
                     int width)
                   : Shape(4, shapeType, coords, pen, brush),
                    length{length},
                    width{width}
{
    CreateParentItem();

    childItems.push_back(new QTreeWidgetItem());
    parentItem->addChild(*(childItems.end() - 1));

    auto endChild = (*(childItems.end() - 1));

    endChild->setText(0, "Length:");
    endChild->setText(1, QString::number(length));
    endChild->setFlags(endChild->flags() | Qt::ItemIsEditable);

    childItems.push_back(new QTreeWidgetItem());
    parentItem->addChild(*(childItems.end() - 1));

    endChild = (*(childItems.end() - 1));

    endChild->setText(0, "Width:");
    endChild->setText(1, QString::number(width));
    endChild->setFlags(endChild->flags() | Qt::ItemIsEditable);

    CreatePenChild();
    CreateBrushChild();
}


void Rectangle::Draw(QWidget* renderArea)
{
    if (!getPainter().isActive())
    {
        getPainter().begin(renderArea); // Ensure the painter is properly started
    }

    getPainter().save(); // Save current state

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawRect(getX(),getY(), length, width);

    if (getSelected())
    {
        QPen highlightPen(Qt::DashLine);
        highlightPen.setColor(Qt::red);
        getPainter().setPen(highlightPen);
        getPainter().setBrush(Qt::NoBrush);
        getPainter().drawRect(getX(), getY(), length, width);
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


double Rectangle::Perimeter() const { return (length * 2) + (width * 2); }
double Rectangle::Area()      const { return length * width; }


bool Rectangle::isPointInside(const QPoint& point) const
{
    QRect rect(getX(), getY(), length, width);
    return rect.contains(point);
}


/************* ACCESSOR FUNCTIONS *************/
int Rectangle::getLength() const { return length; }
int Rectangle::getWidth()  const { return width; }
/**********************************************/

//************* MUTATOR FUNCTIONS *************/
void Rectangle::setLength(int newLength) { length = newLength; }
void Rectangle::setWidth(int newWidth) { width = newWidth; }
void Rectangle::setX(int newX) { Shape::setX(newX); }
void Rectangle::setY(int newY) { Shape::setY(newY); }
/**********************************************/
