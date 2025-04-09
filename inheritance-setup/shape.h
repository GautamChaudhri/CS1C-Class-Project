#ifndef SHAPE_H
#define SHAPE_H

#include <QWidget>
#include <QColor>
#include <QFont>
#include <QPen>
#include <string>
#include <cmath>
#include <vector>
#include <QPainter>

using std::string;

using Qt::GlobalColor;
using Qt::PenCapStyle;
using Qt::PenStyle;
using Qt::PenJoinStyle;
using Qt::BrushStyle;
using Qt::AlignmentFlag;

/****************************************************
* CONSTANTS
* ---------------------------------------------------
* PI - pi used for calculating perimeter and area of
*      shapes (ellipse and circle)
*****************************************************/
const double PI = 3.14;


/****************************************************
* class Shape - Abstract Base Class
*****************************************************/
class Shape
{
    friend bool operator==(const Shape& shape1, const Shape& shape2);
    friend bool operator<(const Shape& shape1, const Shape& shape2);

public:

    /**********************************************************
    * Overloaded Constructor Shape: Class Shape
    * ---------------------------------------------------------
    * ----------------------
    * PRE-CONDITIONS  -
    *
    *      shapeId      :
    *      shapeType    :
    *      x            :
    *      y            :
    *      penColor     :
    *      penWidth     :
    *      penStyle     :
    *      penCapStyle  :
    *      penJoinStyle :
    *      brushColor   :
    *      brushStyle   :
    *
    * POST-CONDITIONS -
    *
    ***********************************************************/
    Shape(int    shapeId,
          string shapeType,
          QPoint coords,
          QPen   pen,
          QBrush brush);

    virtual ~Shape();

    // Need to complete Draw !!
    virtual void Draw() const = 0;
    virtual void Move(int x, int y);

    /**************** ACCESSOR FUNCTIONS ****************/
    int    getShapeId()   const;
    int    getTrackerId() const;
    string getShapeType() const;

    int getX() const;
    int getY() const;

    int          getPenWidth()     const;
    PenStyle     getPenStyle()     const;
    PenCapStyle  getPenCapStyle()  const;
    PenJoinStyle getPenJoinStyle() const;
    QColor       getBrushColor()   const;
    BrushStyle   getBrushStyle()   const;
    QPen         getPen()          const;
    /****************************************************/

    /***************** MUTATOR FUNCTIONS ****************/
    void setShapeId(int shapeId);
    void setTrackerId(int trackerId);
    void setShapeType(string shapeType);

    void setX(int x);
    void setY(int y);

    void setPen(GlobalColor penColor, int penWidth, PenStyle penStyle, PenCapStyle penCapStyle, PenJoinStyle penJoinStyle);
    void setBrush(GlobalColor brushColor, BrushStyle brushStyle);
    /****************************************************/

    virtual double Perimeter() const = 0;
    virtual double Area()      const = 0;

protected:
    QPainter painter;

private:
    int      shapeId;
    int      trackerId;
    string   shapeType;

    QPen     pen;
    QBrush   brush;
    QPoint   coords;

    // Disable Copy Operations
    Shape(Shape& shape) = delete;
};

#endif // SHAPE_H
