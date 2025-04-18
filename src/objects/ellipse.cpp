#include "ellipse.h"

/****************************************************
* class Ellipse - Derived Class
*****************************************************/

Ellipse::Ellipse(int    shapeId,
                  string shapeType,
                  QPoint coords,
                  QPen   pen,
                  QBrush brush,
                  int    a,
                  int    b)
                 : Shape(shapeId,
                         shapeType,
                         coords,
                         pen,
                         brush),
                 a{a},
                 b{b}
{}

void Ellipse::Draw(QWidget* renderArea)
{
    getPainter().begin(renderArea);

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

    getPainter().end();
}

int Ellipse::getA() const { return a; }  // Necessary for parser
int Ellipse::getB() const { return b; }

double Ellipse::Perimeter() const { return 2 * PI * sqrt((pow((2 * a), 2) + pow((2 * b), 2)) / 2); }
double Ellipse::Area()      const { return PI * a * b; }

/****************************************************/

