#ifndef SHAPE_H
#define SHAPE_H

#include <QColor>
#include <QFont>
#include <QPen>
#include <string>
#include <cmath>
#include <vector>

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

    virtual void Move(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    // Accessor Functions
    int getX();
    int getY();

    // Pure Virtual Functions
    virtual double Perimeter() {}
    virtual double Area() {}

private:

    int shapeId;
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


/****************************************************
* class Line - Derived Class
*****************************************************/
class Line : public Shape
{
public:

    Line(     int         shapeId,
         std::string      shapeType,
              int          x,
              int          y,
          Qt::GlobalColor  penColor,
              int          penWidth,
          Qt::PenStyle     penStyle,
          Qt::PenCapStyle  penCapStyle,
          Qt::PenJoinStyle penJoinStyle,
              int          x1,
              int          y1,
              int          x2,
              int          y2);


    double Perimeter() override;

private:
    int x1;
    int y1;
    int x2;
    int y2;

    // Disable Copy Operations
    Line(Line& Line) = delete;
};


/****************************************************
* class Polyline - Derived Class
*****************************************************/
class Polyline : public Shape
{
public:
    Polyline(int shapeId,
             std::string shapeType,
             int x,
             int y,
             Qt::GlobalColor penColor,
             int penWidth,
             Qt::PenStyle penStyle,
             Qt::PenCapStyle penCapStyle,
             Qt::PenJoinStyle penJoinStyle,
             std::vector<int> points);

    double Perimeter() override;

private:
    std::vector < std::vector<int> > points;

    // Disable Copy Operations
    Polyline(Polyline& Polyline) = delete; 
};


/****************************************************
* class Polygon - Derived Class
*****************************************************/
class Polygon : public Shape
{
public:
    Polygon(int shapeId,
            std::string shapeType,
            int x,
            int y,
            Qt::GlobalColor penColor,
            int penWidth,
            Qt::PenStyle penStyle,
            Qt::PenCapStyle penCapStyle,
            Qt::PenJoinStyle penJoinStyle,
            Qt::GlobalColor brushColor,
            Qt::BrushStyle brushStyle,
            std::vector<int> points);


    double Perimeter() override;
    double Area()      override;


private:
    std::vector < std::vector<int> > points;

    // Disable Copy Operations
    Polygon(Polygon& Polygon) = delete; 
};


/****************************************************
* class Rectangle - Derived Class
*****************************************************/
class Rectangle : public Shape
{
public:
    Rectangle(int shapeId,
              std::string shapeType,
              int x,
              int y,
              Qt::GlobalColor penColor,
              int penWidth,
              Qt::PenStyle penStyle,
              Qt::PenCapStyle penCapStyle,
              Qt::PenJoinStyle penJoinStyle,
              int length,
              int width);

    double Perimeter() override;
    double Area()      override;

private:
    int length;
    int width;

    // Disable Copy Operations
    Rectangle(Rectangle& Rectangle) = delete; 
};


/****************************************************
* class Square - Derived Class
*****************************************************/
class Square : public Shape
{
public:
    Square(int shapeId,
           std::string shapeType,
           int x,
           int y,
           Qt::GlobalColor penColor,
           int penWidth,
           Qt::PenStyle penStyle,
           Qt::PenCapStyle penCapStyle,
           Qt::PenJoinStyle penJoinStyle,
           int length);

    double Perimeter() override;
    double Area()      override;

private:
    int length;

    // Disable Copy Operations
    Square(Square& Square) = delete; 
};


/****************************************************
* class Ellipse - Derived Class
*****************************************************/
class Ellipse : public Shape
{
public:
    Ellipse(int shapeId,
            std::string shapeType,
            int x,
            int y,
            Qt::GlobalColor penColor,
            int penWidth,
            Qt::PenStyle penStyle,
            Qt::PenCapStyle penCapStyle,
            Qt::PenJoinStyle penJoinStyle,
            int a,
            int b);

    double Perimeter() override;
    double Area()      override;

private:
    int a;
    int b;

    // Disable Copy Operations
    Ellipse(Ellipse& Ellipse) = delete; 
};


/****************************************************
* class Circle - Derived Class
*****************************************************/
class Circle : public Shape
{
public:
    Circle(int shapeId,
           std::string shapeType,
           int x,
           int y,
           Qt::GlobalColor penColor,
           int penWidth,
           Qt::PenStyle penStyle,
           Qt::PenCapStyle penCapStyle,
           Qt::PenJoinStyle penJoinStyle,
           int r);

    double Perimeter() override;
    double Area()      override;

private:
    int r;

    // Disable Copy Operations
    Circle(Circle& Circle) = delete; 
};


/****************************************************
* class Text - Derived Class
*****************************************************/
class Text : public Shape
{
public:
    Text(int shapeId,
         std::string shapeType,
         int x,
         int y,
         std::string textString,
         Qt::GlobalColor textColor,
         Qt::AlignmentFlag textAlignment,
         int textPointSize,
         std::string textFontFamily,
         QFont::Style textFontStyle,
         QFont::Weight textFontWeight,
         int length,
         int width);

    double Perimeter() override;
    double Area() override;

private:
    int length;
    int width;

    std::string       textString;
    Qt::GlobalColor   textColor;
    Qt::AlignmentFlag textAlignment;
    int               textPointSize;
    std::string       textFontFamily;
    QFont::Style      textFontStyle;
    QFont::Weight     textFontWeight;

    // Disable Copy Operations
    Text(Text& Text) = delete;  
};

#endif // SHAPE_H
