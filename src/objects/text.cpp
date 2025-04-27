#include "text.h"

/****************************************************
* derived class Text - Base Shape
*****************************************************/

Text::Text(string shapeType,
           QPoint coords,
           QString textString,
           GlobalColor   textColor,
           AlignmentFlag textAlignment,
           QFont             font,
           int           length,
           int           width)
        : Shape(shapeType, coords, QPen(), QBrush()),
            textString{textString},
            textColor{textColor},
            textAlignment{textAlignment},
            font{font},
            length{length},
            width{width}
{
    parentItem->setText(0, QString::fromStdString(shapeType));

    for (int i = 0; i < 10; ++i) // 6 being # of data members in shape being displayed for all shapes (JUST FOR TESTING PLEASE CHANGE)
    {
        childItems.push_back(new QTreeWidgetItem());
        parentItem->addChild(childItems[i]);
    }

    // hard coded spaces for each subitem, change as you please
    childItems[0]->setText(0, "Shape ID:");
    childItems[0]->setText(1, QString::number(getShapeId()));

    childItems[1]->setText(0, "Tracker ID:");
    childItems[1]->setText(1, QString::number(getTrackerId()));

    childItems[2]->setText(0, "Shape Type:");
    childItems[2]->setText(1, QString::fromStdString(shapeType));

    childItems[3]->setText(0, "X:");
    childItems[3]->setText(1, QString::number(getX()));
    childItems[3]->setFlags(childItems[3]->flags() | Qt::ItemIsEditable);

    childItems[4]->setText(0, "Y:");
    childItems[4]->setText(1, QString::number(getY()));
    childItems[4]->setFlags(childItems[4]->flags() | Qt::ItemIsEditable);

    childItems[5]->setText(0, "Text:");
    childItems[5]->setText(1, getTextString());
    childItems[5]->setFlags(childItems[4]->flags() | Qt::ItemIsEditable);

    childItems[6]->setText(0, "Alignment:");
    childItems[6]->setFlags(childItems[6]->flags() | Qt::ItemIsEditable);

    childItems[7]->setText(0, "Font:");
    childItems[7]->setFlags(childItems[7]->flags() | Qt::ItemIsEditable);

    childItems[8]->setText(0, "Font Style:");
    childItems[8]->setFlags(childItems[8]->flags() | Qt::ItemIsEditable);

    childItems[9]->setText(0, "Font Weight:");
    childItems[9]->setFlags(childItems[9]->flags() | Qt::ItemIsEditable);
    setShapeId(8);
}


void Text::Draw(QWidget* renderArea)
{
    if (!getPainter().isActive())
    {
        getPainter().begin(renderArea); // Ensure the painter is properly started
    }

    getPainter().save(); // Save current state

    // Draw the text
    getPainter().setPen(textColor);
    getPainter().setFont(font);
    getPainter().drawText(QRect(getX(), getY(), length, width), textAlignment, textString);

    if (getSelected())
    {
        // Draw the highlight rectangle
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


bool Text::isPointInside(const QPoint& point) const
{
    QRect rect(getX(), getY(), length, width);
    return rect.contains(point);
}


double Text::Perimeter() const { return (length * 2) + (width * 2); }
double Text::Area()      const { return length * width; }

/************* ACCESSOR FUNCTIONS *************/
int           Text::getLength()        const { return length; }
int           Text::getWidth()         const { return width; }
QString       Text::getTextString()    const { return textString; }
GlobalColor   Text::getTextColor()     const { return textColor; }
QFont         Text::getFont()          const { return font; }
AlignmentFlag Text::getTextAlignment() const { return textAlignment; }
int           Text::getFontStyle()     const { return font.style();}
QFont::Weight Text::getFontWeight()    const { return font.weight();}
/**********************************************/

