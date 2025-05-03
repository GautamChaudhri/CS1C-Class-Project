#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <cmath>
#include <QWidget>
#include <QColor>
#include <QFont>
#include <QPen>
#include <QPainter>
#include <QList>
#include <QPolygon>
#include <QTreeWidget>
#include "vector.h"


using std::string;

using Qt::GlobalColor;
using Qt::PenCapStyle;
using Qt::PenStyle;
using Qt::PenJoinStyle;
using Qt::BrushStyle;
using Qt::AlignmentFlag;

const double PI = 3.14; /// Global constant PI used for calculating perimater and area


static int globalTracker = 0; /// Global static int used for creating trackerIds

/**
 * \defgroup <Shape> Shapes
 * \interface <Shape> shape.h "objects/shape.h"
 *
 * @brief The Shape Abstract Base Class
 */

class Shape
{
    /**
     * @brief operator == - Overloaded equality operator for comparing two shapeId's
     * @param shape1
     * @param shape2
     * @return
     */
    friend bool operator==(const Shape& shape1, const Shape& shape2);
    /**
     * @brief operator < - Overloaded less than operator for comparing two shapeId's
     * @param shape1
     * @param shape2
     * @return
     */
    friend bool operator<(const Shape& shape1, const Shape& shape2);

public:

    /**
     * @brief Shape Constructor
     * @param shapeType - string representing shape type, (Line, Circle, etc)
     * @param coords - QPoint with coordinates of the shape
     * @param pen - QPen for the outline of the shape
     * @param brush - QBrush for the fill of the shape
     */
    Shape(string shapeType,
          QPoint coords,
          QPen   pen,
          QBrush brush);

    /**
     * @brief ~Shape Destructor
     */
    virtual ~Shape();

    /**
     * @brief Draw - Draws the shape to the associated renderArea
     * @param renderArea - QWidget to be drawn on
     *
     * @pure
     */
    virtual void Draw(QWidget* renderArea) = 0;

    /**
     * @brief Move - Moves the shape to the x and y coords
     * @param x - x coordinate
     * @param y - y coordinate
     */
    virtual void Move(int x, int y);

    /**
     * @brief Perimeter - Returns the perimeter of the shape
     * @return
     *
     * @pure
     */
    virtual double Perimeter() const = 0;

    /**
     * @brief Area - Returns the area of the shape
     * @return
     *
     * @pure
     */
    virtual double Area()      const = 0;

    /**
     * @brief isPointInside - Returns true if point is inside the shape
     * @param point - QPoint being checked
     * @return
     *
     * @pure
     */
    virtual bool isPointInside(const QPoint& point) const = 0;

    /**
     * @brief CreateParentItem - Adds data cooresponding to all shapes to parentItem for a QTreeWidget
     */
    void CreateParentItem();

    /**
     * @brief CreatePenChild - Adds pen data to penItems vector for a QTreeWidget
     */
    void CreatePenChild();

    /**
     * @brief CreateBrushChild - Adds brush data to brushItems vector for a QTreeWidget
     */
    void CreateBrushChild();

    /**
     * @brief CreatePointsChild - Adds points data to pointsItems vector for a QTreeWidget
     * @param POINTS_NUM - Number of points being added
     */
    void CreatePointsChild(const int POINTS_NUM);

    /// Accessor Functions - Returns the data named after them
    int    getShapeId()   const;
    int    getTrackerId() const;
    string getShapeType() const;
    bool   getSelected()  const;

    int getX() const;
    int getY() const;

    QPainter& getPainter();
    QTreeWidgetItem* getParentItem();
    alpha::vector<QTreeWidgetItem*>& getChildItems();
    alpha::vector<QTreeWidgetItem*>& getPointsItems();
    alpha::vector<QTreeWidgetItem*>& getPenItems();
    alpha::vector<QTreeWidgetItem*>& getBrushItems();

    int          getPenWidth()      const;
    PenStyle     getPenStyle()      const;
    PenCapStyle  getPenCapStyle()   const;
    PenJoinStyle getPenJoinStyle()  const;
    QColor       getPenColor()      const;
    QColor       getBrushColor()    const;
    BrushStyle   getBrushStyle()    const;
    QPen         getPen()           const;
    QBrush       getBrush()         const;
    QPoint       getPoints()        const;
    int          getChildEnd()      const; /** Returns the dereferenced childItems.end() - 1 for the last initialized element of the vector */
    int          getPenItemsEnd()   const; /** Returns the dereferenced penItems.end() - 1 for the last initialized element of the vector */
    int          getBrushItemsEnd() const; /** Returns the dereferenced brushItems.end() - 1 for the last initialized element of the vector */
    /// Accessor Functions

    /// Mutator Functions - Sets the data of the item to the passed param
    void setShapeId(int shapeId);
    void setTrackerId(int trackerId);
    void setShapeType(string shapeType);
    void setSelected(bool selected);

    void setX(int x);
    void setY(int y);

    void setPen(GlobalColor penColor, int penWidth, PenStyle penStyle, PenCapStyle penCapStyle, PenJoinStyle penJoinStyle);
    void setBrush(GlobalColor brushColor, BrushStyle brushStyle);

    // These functions make it easier to change pen and brush properties in RenderAreaManager::modifyShape()
    QPen& setInternalPen();
    QBrush& setInternalBrush();
    /// Mutator Functions

protected:
    QTreeWidgetItem* parentItem;                 ///< QTreeWidgetItem* holding treeWidget data of each shape
    alpha::vector<QTreeWidgetItem*> childItems;  ///< vector of QTreeWidgetItem* holding data of all child items in parentItem
    alpha::vector<QTreeWidgetItem*> pointsItems; ///< vector of QTreeWidgetItem* holding data of all points (besides coords) in parentItem
    alpha::vector<QTreeWidgetItem*> penItems;    ///< vector of QTreeWidgetItem* holding data of all pen items
    alpha::vector<QTreeWidgetItem*> brushItems;  ///< vector of QTreeWidgetItem* holding data of all brush items

private:
    int      shapeId; ///< int representing the id of a shape, each shapeType is given one id, Line = 1, Polyline = 2, etc.
    int      trackerId = globalTracker++; ///< int representing the unique id of each shape, each individual shape has its own trackerId
    string   shapeType; ///< string representing the type of shape, (Line, Circle, etc)

    QPen     pen;    ///< QPen for the outline
    QBrush   brush;  ///< QBrush for the fill
    QPoint   coords; ///< QPoint for the coordinates of the shape

    QPainter painter; ///< QPainter used to paint the shape onto a rendering area

    bool isSelected = false; ///< Shows the state of the shape, if it is currently selected by the user

    // Disable Copy Operations
    Shape(Shape& shape) = delete;
    Shape& operator=(Shape& object) = delete;
};

#endif // SHAPE_H

