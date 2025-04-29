#include "ellipse.h"

/****************************************************
* derived class Ellipse - Base Shape
*****************************************************/

Ellipse::Ellipse(string shapeType,
                  QPoint coords,
                  QPen   pen,
                  QBrush brush,
                  int    a,
                  int    b)
                 : Shape(shapeType,
                         coords,
                         pen,
                         brush),
                 a{a},
                 b{b}
{
    parentItem->setText(0, QString::fromStdString(shapeType));

    for (int i = 0; i < 9; ++i)
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

        childItems[5]->setText(0, "Semi-Minor Axis:");
        childItems[5]->setText(1, QString::number(a));
        childItems[5]->setFlags(getChildItems()[5]->flags() | Qt::ItemIsEditable);

        childItems[6]->setText(0, "Semi-Major Axis::");
        childItems[6]->setText(1, QString::number(b));
        childItems[6]->setFlags(getChildItems()[6]->flags() | Qt::ItemIsEditable);

        childItems[7]->setText(0, "Pen:");
        childItems[7]->setFlags(childItems[7]->flags() | Qt::ItemIsEditable);

        childItems[8]->setText(0, "Brush:");
        childItems[8]->setFlags(childItems[8]->flags() | Qt::ItemIsEditable);
    setShapeId(6);
}


void Ellipse::Draw(QWidget* renderArea)
{
    if (!getPainter().isActive())
    {
        getPainter().begin(renderArea); // Ensure the painter is properly started
    }

    getPainter().save(); // Save current state

    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawEllipse(getPoints(), a, b);

    if (getSelected())
    {
        QPen highlightPen(Qt::DashLine);
        highlightPen.setColor(Qt::red);
        getPainter().setPen(highlightPen);
        getPainter().setBrush(Qt::NoBrush);
        getPainter().drawRect(getX() - a, getY() - b, a*2, b*2); //probably a better way to do the x and y but I am lazy
    }

    //draws the shape id text
    QFont font;
    getPainter().setPen(Qt::black);
    font.setPointSize(10); // Sets the font size
    getPainter().setFont(font);
    getPainter().drawText(getX() - a, getY() - b, QString("ID: " + QString::number(getShapeId())));

    getPainter().restore(); // Restore saved state

    getPainter().end(); // End the painter session
}


double Ellipse::Perimeter() const { return 2 * PI * sqrt((pow((2 * a), 2) + pow((2 * b), 2)) / 2); }
double Ellipse::Area()      const { return PI * a * b; }


bool Ellipse::isPointInside(const QPoint& point) const
{
    QRect rect(getX() - a, getY() - b, a*2, b*2);
    return rect.contains(point);
}


/************* ACCESSOR FUNCTIONS *************/
int Ellipse::getA() const { return a; }
int Ellipse::getB() const { return b; }
/**********************************************/

/************* MUTATOR FUNCTIONS *************/
void Ellipse::setA(int newA) { a = newA; }
void Ellipse::setB(int newB) { b = newB; }
void Ellipse::setX(int newX) { Shape::setX(newX); }
void Ellipse::setY(int newY) { Shape::setY(newY); }
/**********************************************/