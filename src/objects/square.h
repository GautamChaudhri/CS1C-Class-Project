#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"

/**
 * \ingroup Shapes
 * \class Square square.h "objects/square.h"
 *
 * @brief The Square class
 */
class Square : public Shape
{
public:
    /**
     * @brief Square
     * @param shapeType - Used in Shape constructor MIL
     * @param coords - Used in Shape constructor MIL
     * @param pen - Used in Shape constructor MIL
     * @param brush - Used in Shape constructor MIL
     * @param length - Side length of the Square
     */
    Square(string shapeType,
           QPoint coords,
           QPen   pen,
           QBrush brush,
           int length);

    /**
     * @brief Draw - Draws a Square at the assigned coords
     * @param renderArea - The renderArea being drawn on
     */
    void Draw(QWidget* renderArea) override;

    /**
     * @brief Perimeter - Returns the perimater of the Square
     * @return
     */
    double Perimeter() const override;

    /**
     * @brief Area - Returns the area of the Square
     * @return
     */
    double Area()      const override;

    /**
     * @brief isPointInside - Returns True if point is inside the Square
     * @param point - point being read
     * @return
     */
    bool isPointInside(const QPoint& point) const override;

    /// Accessor Functions
    int getLength() const;

    /// Mutator Functions
    void setLength(int newLength);
    void setX(int newX);
    void setY(int newY);

private:
    int length; ///< side length of the Square
};

#endif // SQUARE_H
