#include "circle.h"

/****************************************************
* derived class Circle - Base Shape
*****************************************************/

Circle::Circle(int    shapeId,
               string shapeType,
               QPoint coords,
               QPen   pen,
               QBrush brush,
               int    r)
    : Shape(shapeId,
            shapeType,
            coords,
            pen,
            brush),
    r{r}
{
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
