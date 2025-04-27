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
/**********************************************/
