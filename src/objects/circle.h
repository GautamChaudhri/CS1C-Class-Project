#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

/**
 * \ingroup Shapes
 * \class Circle circle.h "objects/circle.h"
 *
 * @brief The Circle class
 */

class Circle : public Shape
{
public:
    /**
     * @brief Circle Constructor
     * @param shapeType - Used in Shape constructor MIL
     * @param coords - Used in Shape constructor MIL
     * @param pen - Used in Shape constructor MIL
     * @param brush - Used in Shape constructor MIL
     * @param r - int radius
     */
    Circle(string shapeType,
           QPoint coords,
           QPen   pen,
           QBrush brush,
           int r);

    /**
     * @brief Draw - Draws a circle at the assigned coords with the given radius
     * @param renderArea - The renderArea being drawn on
     */
    void Draw(QWidget* renderArea) override;

    /**
     * @brief Perimeter - Returns the perimeter of  the circle
     * @return
     */
    double Perimeter() const override;

    /**
     * @brief Area - Returns the area of the circle
     * @return
     */
    double Area()      const override;

    /**
     * @brief isPointInside - Returns True if point is inside the circle
     * @param point - point being read
     * @return
     */
    bool isPointInside(const QPoint& point) const override;

    /**
     * @brief getR - Accessor - Returns the radius
     * @return
     */
    int getR() const;

    /// Mutator Functions
    void setR(int radius);
    void setX(int x);
    void setY(int y);   
    /// Mutator Functions

private:
    int r; ///< int radius of the circle
};

#endif // CIRCLE_H

