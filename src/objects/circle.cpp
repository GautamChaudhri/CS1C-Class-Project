#include "circle.h"

/****************************************************
* derived class Circle - Base Shape
*****************************************************/

Circle::Circle(int    trackerId,
               string shapeType,
               QPoint coords,
               QPen   pen,
               QBrush brush,
               int    r)
       : Shape(trackerId,
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
