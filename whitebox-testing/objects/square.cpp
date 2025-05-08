#include "square.h"

/****************************************************
* derived class Square - Base Shape
*****************************************************/

Square::Square(string shapeType,
               QPoint coords,
               QPen   pen,
               QBrush brush,
               int length)
             : Shape(5, shapeType, coords, pen, brush),
               length{length}
{
    CreateParentItem();

    childItems.push_back(new QTreeWidgetItem());
    parentItem->addChild(*(childItems.end() - 1));

    auto endChild = (*(childItems.end() - 1));

    endChild->setText(0, "Length:");
    endChild->setText(1, QString::number(length));
    endChild->setFlags(endChild->flags() | Qt::ItemIsEditable);

    CreatePenChild();
    CreateBrushChild();
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

//************* MUTATOR FUNCTIONS *************/
void Square::setLength(int newLength) { length = newLength; }
void Square::setX(int newX) { Shape::setX(newX); }
void Square::setY(int newY) { Shape::setY(newY); }
/**********************************************/
