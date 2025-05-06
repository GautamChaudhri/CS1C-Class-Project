#ifndef POLYLINE_H
#define POLYLINE_H

#include "shape.h"

/**
 * \ingroup Shapes
 * \class Polyline polyline.h "objects/polyline.h"
 *
 * @brief The Polyline class
 */
class Polyline : public Shape
{
public:
    /**
     * @brief Polyline
     * @param shapeType - Used in Shape constructor MIL
     * @param coords - Used in Shape constructor MIL
     * @param pen - Used in Shape constructor MIL
     * @param brush - Used in Shape constructor MIL
     * @param pointsList - List of QPoints for each point of the Polyline
     */
    Polyline(string shapeType,
             QPoint coords,
             QPen   pen,
             QBrush brush,
             QPolygon pointsList);

    /**
     * @brief Draw - Draws a Polyline at the assigne coords with points in the pointsList
     * @param renderArea - The renderArea being drawn on
     */
    void Draw(QWidget* renderArea) override;

    /**
     * @brief Move - Moves the Polyline to the passed x and y coordinates
     * @param x - x coordinate
     * @param y - y coordinate
     */
    void Move(int x, int y) override;

    /**
     * @brief Perimeter -  Returns the perimater of the Polyline
     * @return
     */
    double Perimeter() const override;

    /**
     * @brief Area - Returns 0 (Needs to have implementation to avoid being seen as virtual
     * @return
     */
    double Area() const override {return 0;}

    /**
     * @brief isPointInside - Returns True if point is inside the Polyline
     * @param point - points being read
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

#endif // POLYLINE_H
