#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

/**
 * \ingroup Shapes
 * \class Rectangle rectangle.h "objects/rectangle.h"
 *
 * @brief The Rectangle class
 */
class Rectangle : public Shape
{
public:
    /**
     * @brief Rectangle
     * @param shapeType - Used in Shape constructor MIL
     * @param coords - Used in Shape constructor MIL
     * @param pen - Used in Shape constructor MIL
     * @param brush - Used in Shape constructor MIL
     * @param length - Length of the Rectangle
     * @param width - Width of the Rectangle
     */
    Rectangle(string shapeType,
              QPoint coords,
              QPen   pen,
              QBrush brush,
              int length,
              int width);

    /**
     * @brief Draw - Draws a Rectangle at the assigned coords
     * @param renderArea - The renderArea being drawn on
     */
    void Draw(QWidget* renderArea) override;

    /**
     * @brief Perimeter - Returns the perimeter of the Rectangle
     * @return
     */
    double Perimeter() const override;

    /**
     * @brief Area - Returns the area of the Rectangle
     * @return
     */
    double Area()      const override;

    /**
     * @brief isPointInside - Returns True if point is inside the Rectangle
     * @param point - point being read
     * @return
     */
    bool isPointInside(const QPoint& point) const override;

    /// Accessor Functions
    int getLength() const;
    int getWidth()  const;

    /// Mutator Functions
    void setLength(int newLength);
    void setWidth(int newWidth);
    void setX(int newX);
    void setY(int newY);

private:
    int length; ///< length of the rectangle
    int width; ///< width of the rectangle
};

#endif // RECTANGLE_H

