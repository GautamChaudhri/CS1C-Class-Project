#ifndef LINE_H
#define LINE_H

#include "shape.h"

/**
 * \ingroup Shapes
 * \class Line line.h "objects/line.h"
 *
 * @brief The Line class
 */
class Line : public Shape
{
public:
    /**
     * @brief Line Constructor
     * @param shapeType - Used in Shape constructor MIL
     * @param coords - Used in Shape constructor MIL
     * @param pen - Used in Shape constructor MIL
     * @param brush - Used in Shape constructor MIL
     * @param startPoint - Point representing the start of the line
     * @param endPoint - Point representing the end of the line
     */
    Line(string shapeType,
         QPoint coords,
         QPen   pen,
         QBrush brush,
         QPoint startPoint,
         QPoint endPoint);

    /**
     * @brief Draw - Draws a line from startPoint to endPoint
     * @param renderArea - The renderArea being drawn on
     */
    void Draw(QWidget* renderArea) override;

    /**
     * @brief Move - Moves the Line coords to the passed x and y
     * @param x - x coordinate
     * @param y - y coordinate
     */
    void Move(int x, int y) override;

    /**
     * @brief Perimeter - Returns the perimeter of the Line
     * @return
     */
    double Perimeter() const override;

    /**
     * @brief Area - Returns 0, necessary override to avoid being seen as Abstract
     * @return
     */
    double Area() const override { return 0; }  // Need to implement this to instantiate Line

    /**
     * @brief isPointInside - Returns True if point is inside the Line
     * @param point - point being read
     * @return
     */
    bool isPointInside(const QPoint& point) const override;

    /// Accessor Functions
    QPoint getStartPoint() const;
    QPoint getEndPoint()   const;
    /// Accessor Functions

    /// Mutator Functions
    void setStartPoint(const QPoint& newStartPoint);
    void setEndPoint(const QPoint& newEndPoint);
    void setX(int newX);
    void setY(int newY);
    /// Mutator Functions

private:
    QPoint startPoint; ///< Starting point of the Line
    QPoint endPoint; ///< Ending point of the line
};

#endif // LINE_H
