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
    Shape(int    shapeId,
         std::string shapeType,
             int    x,
             int    y,
          Qt::GlobalColor penColor,
               int    penWidth,
          Qt::PenStyle penStyle,
          Qt::PenCapStyle penCapStyle,
          Qt::PenJoinStyle penJoinStyle,
          Qt::GlobalColor brushColor,
          Qt::BrushStyle brushStyle)
        : shapeId{shapeId},
          shapeType{shapeType},
          x{x},
          y{y},
          penColor{penColor},
          penWidth{penWidth},
          penStyle{penStyle},
          penCapStyle{penCapStyle},
          penJoinStyle{penJoinStyle},
          brushColor{brushColor},
          brushStyle{brushStyle};

    virtual ~Shape() {}

    virtual void Draw() = 0;
    virtual void Move(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

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
    int    setShapeId(int shapeId);
    int    setTrackerId(int trackerId);
    string setShapeType(string shapeType);

    int setX(int x);
    int setY(int y);

    Qt::GlobalColor  setGlobalColor(Qt::GlobalColor globalColor);
    int              setPenWidth(int penWidth);
    Qt::PenStyle     setPenStyle(Qt::PenStyle penStyle);
    Qt::PenCapStyle  setPenCapStyle(Qt::PenCapStyle penCapStyle);
    Qt::PenJoinStyle setPenJoinStyle(Qt::PenJoinStyle penJoinStyle);
    Qt::GlobalColor  setBrushColor(Qt::GlobalColor brushColor);
    Qt::BrushStyle   setBrushStyle(Qt::BrushStyle brushStyle);
    /****************************************************/

    virtual double Perimeter() {}
    virtual double Area()      {}

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

/****************************************************
* class Line - Derived Class
*****************************************************/
class Line : public Shape
{
public:
    Line(int shapeId,
         std::string shapeType,
         int x,
         int y,
         Qt::GlobalColor penColor,
         int penWidth,
         Qt::PenStyle penStyle,
         Qt::PenCapStyle penCapStyle,
         Qt::PenJoinStyle penJoinStyle,
         int x1,
         int y1,
         int x2,
         int y2)
       : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
         x1{x1},
         y1{y1},
         x2{x2},
         y2{y2} {}


    double Perimeter() override { return sqrt(pow((x1 - x2),2) + pow((y1 - y2),2)); }

private:
    int x1;
    int y1;
    int x2;
    int y2;

    // Disable Copy Operations
    Line(Line& Line) = delete;
};

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
             std::vector<int> points)
           : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
             points{points} {}

    double Perimeter() override
    {
        double perimeter;
        perimeter = 0;

        int vecSize;
        vecSize = points.size() - 1;

        for(int i = 0; i < vecSize; i ++)
        {
            perimeter += sqrt(pow((points[i][0] - points[i + 1][0]), 2) + pow((points[i][1] - points[i + 1][1]), 2));
        };

        return perimeter;
    }

private:
    std::vector < std::vector<int> > points;

    // Disable Copy Operations
    Polyline(Polyline& Polyline) = delete; 
};

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
            std::vector<int> points)
          : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, brushColor, brushStyle),
            points{points} {}

    double Perimeter() override
    {
        double perimeter;

        perimeter = sqrt(pow((points[0][0] - points[1][0]), 2) + pow((points[0][1] - points[1][1]), 2) * points.size());

        return perimeter;
    }

    double Area() override
    {
        double apothem;

        apothem = (sqrt(pow((points[0][0] - points[1][0]), 2) + pow((points[0][1] - points[1][1]), 2))) / tan(180 / points.size());

        return (Perimeter() * apothem) / 2;
    }


private:
    std::vector < std::vector<int> > points;

    // Disable Copy Operations
    Polygon(Polygon& Polygon) = delete; 
};

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
              int width)
            : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
              length{length},
              width{width} {}

    double Perimeter() override { return length*2 + width*2;}
    double Area() override      { return length*width;}

private:
    int length;
    int width;

    // Disable Copy Operations
    Rectangle(Rectangle& Rectangle) = delete; 
};

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
           int length)
         : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
           length{length} {}

    double Perimeter() override { return length*4;}
    double Area() override      { return pow(length,2);}

private:
    int length;

    // Disable Copy Operations
    Square(Square& Square) = delete; 
};

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
            int b)
          : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
            a{a},
            b{b} {}
    double Perimeter() override { return 2*PI*sqrt((pow((2*a), 2) + pow((2*b), 2))/2); }
    double Area() override { return PI*a*b; }

private:
    int a;
    int b;

    // Disable Copy Operations
    Ellipse(Ellipse& Ellipse) = delete; 
};

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
           int r)
         : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
           r{r} {}
    double Perimeter() override { return 2*PI*r ; }
    double Area() override { return PI*pow(r, 2); }

private:
    int r;

    // Disable Copy Operations
    Circle(Circle& Circle) = delete; 
};

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
         int width)
       : Shape(shapeId, shapeType, x, y, Qt::GlobalColor(), 0, Qt::PenStyle(), Qt::PenCapStyle(), Qt::PenJoinStyle(), Qt::GlobalColor(), Qt::BrushStyle()),
         textString{textString},
         textColor{textColor},
         textAlignment{textAlignment},
         textPointSize{textPointSize},
         textFontFamily{textFontFamily},
         textFontStyle{textFontStyle},
         textFontWeight{textFontWeight},
         length{length},
         width{width} {}

    double Perimeter() override { return length*2 + width*2;}
    double Area() override      { return length*width;}

private:
    int length;
    int width;
    std::string textString;
    Qt::GlobalColor textColor;
    Qt::AlignmentFlag textAlignment;
    int textPointSize;
    std::string textFontFamily;
    QFont::Style textFontStyle;
    QFont::Weight textFontWeight;

    // Disable Copy Operations
    Text(Text& Text) = delete;  
};

#endif // SHAPE_H
