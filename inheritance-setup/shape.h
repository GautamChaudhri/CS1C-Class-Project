#ifndef SHAPE_H
#define SHAPE_H

#include <QColor>
#include <QFont>
#include <QPen>
#include <string>
#include <cmath>
#include <vector>

using std::string;

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
    Shape(     int          shapeId,
          std::string       shapeType,
          int          x,
          int          y,
          Qt::GlobalColor  penColor,
          int          penWidth,
          Qt::PenStyle     penStyle,
          Qt::PenCapStyle  penCapStyle,
          Qt::PenJoinStyle penJoinStyle,
          Qt::GlobalColor  brushColor,
          Qt::BrushStyle   brushStyle);

    virtual ~Shape();

    // Need to complete Draw !!
    virtual void Draw() = 0;
    virtual void Move(int x, int y);

    /**************** ACCESSOR FUNCTIONS ****************/
    int    getShapeId()   const;
    int    getTrackerId() const;
    string getShapeType() const;

    int getX() const;
    int getY() const;

    Qt::GlobalColor  getGlobalColor()  const;
    int              getPenWidth()     const;
    Qt::PenStyle     getPenStyle()     const;
    Qt::PenCapStyle  getPenCapStyle()  const;
    Qt::PenJoinStyle getPenJoinStyle() const;
    Qt::GlobalColor  getBrushColor()   const;
    Qt::BrushStyle   getBrushStyle()   const;
    /****************************************************/

    /***************** MUTATOR FUNCTIONS ****************/
    void setShapeId(int shapeId);
    void setTrackerId(int trackerId);
    void setShapeType(string shapeType);

    void setX(int x);
    void setY(int y);

    void setGlobalColor(Qt::GlobalColor globalColor);
    void setPenWidth(int penWidth);
    void setPenStyle(Qt::PenStyle penStyle);
    void setPenCapStyle(Qt::PenCapStyle penCapStyle);
    void setPenJoinStyle(Qt::PenJoinStyle penJoinStyle);
    void setBrushColor(Qt::GlobalColor brushColor);
    void setBrushStyle(Qt::BrushStyle brushStyle);
    /****************************************************/

    virtual double Perimeter() const = 0;
    virtual double Area()      const = 0;

private:

    int shapeId;
    int trackerId;
    std::string shapeType;

    int x;
    int y;

    Qt::GlobalColor penColor;
    int penWidth;
    Qt::PenStyle penStyle;
    Qt::PenCapStyle penCapStyle;
    Qt::PenJoinStyle penJoinStyle;
    Qt::GlobalColor brushColor;
    Qt::BrushStyle brushStyle;

    // Disable Copy Operations
    Shape(Shape& shape) = delete;
};

#endif // SHAPE_H
