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
    setShapeId(6);

    CreateParentItem();
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
