#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"

/**
 * \ingroup Shapes
 * \class Polygon polygon.h "objects/polygon.h"
 *
 * @brief The Polygon class
 */
class Polygon : public Shape
{
public:
    /**
     * @brief Polygon Constructor
     * @param shapeType - Used in Shape constructor MIL
     * @param coords - Used in Shape constructor MIL
     * @param pen - Used in Shape constructor MIL
     * @param brush - Used in Shape constructor MIL
     * @param pointsList - List of QPoints for each point of the Polygon
     */
    Polygon(string shapeType,
             QPoint coords,
             QPen   pen,
             QBrush brush,
             QPolygon pointsList);

    /**
     * @brief Draw - Draws a Polygon at the assigned coords with points in the pointsList
     * @param renderArea - The renderArea being drawn on
     */
    void Draw(QWidget* renderArea) override;

    /**
     * @brief Move - Moves the Polygon to the passed x and y coordinates
     * @param x - x coordinate
     * @param y - y coordinate
     */
    void Move(int x, int y) override;

    /**
     * @brief Perimeter - Returns the perimeter of the Polygon
     * @return
     */
    double Perimeter() const override;

    /**
     * @brief Area - Returns the area of the Polygon
     * @return
     */
    double Area() const override;

    /**
     * @brief isPointInside - Returns True if point is inside the Polygon
     * @param point - point being read
     * @return
     */
    bool isPointInside(const QPoint& point) const override;

    /**
     * @brief getPointsList - Returns the pointsList by value
     * @return
     */
    QPolygon getPointsList() const;

    /// Mutator Functions
    /**
     * @brief setPointsList - Sets the pointsList to the passed newPointsList
     * @param newPointsList - New list of points for pointsList to take
     */
    void setPointsList(const QPolygon& newPointsList);
    void setX(int newX);
    void setY(int newY);

private:
    QPolygon pointsList; ///< list of points
};
#endif // POLYGON_H
