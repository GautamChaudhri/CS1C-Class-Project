#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

/**
 * \ingroup Shapes
 * \class Ellipse ellipse.h "objects/ellipse.h"
 *
 * @brief The Ellipse class
 */
class Ellipse : public Shape
{
public:
    /**
     * @brief Ellipse Constructor
     * @param shapeType - Used in Shape constructor MIL
     * @param coords - Used in Shape constructor MIL
     * @param pen - Used in Shape constructor MIL
     * @param brush - Used in Shape constructor MIL
     * @param a - The Semi-Minor axis of the Ellipse
     * @param b - The Semi-Major axis of the Ellipse
     */
    Ellipse(string shapeType,
            QPoint coords,
            QPen   pen,
            QBrush brush,
            int    a,
            int    b);

    /**
     * @brief Draw - Draws the ellipse to the passed renderArea
     * @param renderArea - The renderArea which the ellipse is drawn to
     */
    void Draw(QWidget* renderArea) override;

    /**
     * @brief Perimeter - Returns the perimeter of the ellipse
     * @return
     */
    double Perimeter() const override;

    /**
     * @brief Area - Returns the area of the ellipse
     * @return
     */
    double Area()      const override;

    /**
     * @brief isPointInside - Returns True if point is inside the circle
     * @param point - point being read
     * @return
     */
    bool isPointInside(const QPoint& point) const override;

    /// Accessor Functions
    int getA() const;
    int getB() const;
    /// Accessor Functions

    /// Mutator Functions
    void setA(int newA);
    void setB(int newB);
    void setX(int newX);
    void setY(int newY);
    /// Mutator Functions

private:
    int a; ///< Semi-Minor Axis
    int b; ///< Semi-Major Axis
};

#endif // ELLIPSE_H
