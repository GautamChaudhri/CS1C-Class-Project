#include "square.h"

/****************************************************
* derived class Square - Base Shape
*****************************************************/

Square::Square(string shapeType,
               QPoint coords,
               QPen   pen,
               QBrush brush,
               int length)
             : Shape(shapeType, coords, pen, brush),
               length{length}
{
    setShapeId(5);
    CreateParentItem();


    // parentItem->setText(0, QString::fromStdString(shapeType));
    
    // for (int i = 0; i < 3; ++i)
    // {
    //     childItems.push_back(new QTreeWidgetItem());
    //     parentItem->addChild(childItems[i + 5]);
    // }

    // childItems[5]->setText(0, "Length:");
    // childItems[5]->setText(1, QString::number(getLength()));
    // childItems[5]->setFlags(getChildItems()[5]->flags() | Qt::ItemIsEditable);

    // childItems[6]->setText(0, "Pen:");
    // childItems[6]->setFlags(childItems[6]->flags() | Qt::ItemIsEditable);

    // childItems[7]->setText(0, "Brush:");
    // childItems[7]->setFlags(childItems[7]->flags() | Qt::ItemIsEditable);
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