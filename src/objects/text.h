#ifndef TEXT_H
#define TEXT_H

#include "shape.h"

/**
 * \ingroup Shapes
 * \class Text text.h "objects/text.h"
 *
 * @brief The Text class
 */
class Text : public Shape
{
public:
    /**
     * @brief Text
     * @param shapeType - Used in Shape constructor MIL
     * @param coords - Used in Shape constructor MIL
     * @param textString - String of text being displayed
     * @param textColor - Color of text
     * @param textAlignment - Alignment of text
     * @param font - Text font
     * @param length - Length of text box
     * @param width - Width of text box
     */
    Text(string shapeType,
         QPoint coords,
         QString textString,
         GlobalColor   textColor,
         AlignmentFlag textAlignment,
         QFont font,
         int length,
         int width);

    /**
     * @brief Draw - Draws the text to the assigned coords
     * @param renderArea - The renderArea being drawn on
     */
    void Draw(QWidget* renderArea) override;

    /**
     * @brief Perimeter - Returns the perimater of the text box
     * @return
     */
    double Perimeter() const override;

    /**
     * @brief Area - Returns the area of the text box
     * @return
     */
    double Area()      const override;

    /**
     * @brief isPointInside - Returns True if point is inside the text box
     * @param point - point being read
     * @return
     */
    bool isPointInside(const QPoint& point) const override;

    /// Accessor Functions
    int           getLength()        const;
    int           getWidth()         const;
    QString       getTextString()    const;
    GlobalColor   getTextColor()     const;
    QFont         getFont()          const;
    AlignmentFlag getTextAlignment() const;
    int           getFontStyle()     const;
    QFont::Weight getFontWeight()    const;

    /// Mutator Functions
    void setText(QString text);
    void setLength(int newLength);
    void setWidth(int newWidth);
    void setX(int newX);
    void setY(int newY);
    void setAlignment(Qt::AlignmentFlag alignment);
    QFont& setInternalFont();


private:
    int length; ///< length of text box
    int width; ///< width of text box

    QString       textString; ///< string of text being displayed
    GlobalColor   textColor; ///< text color
    QFont         font; ///< text font
    AlignmentFlag textAlignment; ///< text alignment
};

#endif // TEXT_H
