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
    setShapeId(8);
    CreateParentItem();

    childItems.push_back(new QTreeWidgetItem());
    parentItem->addChild(*(childItems.end() - 1));

    auto endChild = (*(childItems.end() - 1));

    endChild->setText(0, "Text:");
    endChild->setText(1, getTextString());
    endChild->setFlags(endChild->flags() | Qt::ItemIsEditable);

    childItems.push_back(new QTreeWidgetItem());
    parentItem->addChild(*(childItems.end() - 1));

    endChild = (*(childItems.end() - 1));

    endChild->setText(0, "Alignment:");

    childItems.push_back(new QTreeWidgetItem());
    parentItem->addChild(*(childItems.end() - 1));

    endChild = (*(childItems.end() - 1));

    endChild->setText(0, "Font:");

    childItems.push_back(new QTreeWidgetItem());
    parentItem->addChild(*(childItems.end() - 1));

    endChild = (*(childItems.end() - 1));

    endChild->setText(0, "Font Style:");

    childItems.push_back(new QTreeWidgetItem());
    parentItem->addChild(*(childItems.end() - 1));

    endChild = (*(childItems.end() - 1));

    endChild->setText(0, "Font Weight:");
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

/************* MUTATOR FUNCTIONS *************/
void Text::setText(QString text) { textString = text;}
void Text::setLength(int newLength) { length = newLength; }
void Text::setWidth(int newWidth) { width = newWidth; }
void Text::setX(int newX) { Shape::setX(newX); }
void Text::setY(int newY) { Shape::setY(newY); }
/**************************************************/
