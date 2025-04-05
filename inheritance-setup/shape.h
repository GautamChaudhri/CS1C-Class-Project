#ifndef SHAPE_H
#define SHAPE_H

#include <QColor>
#include <QFont>
#include <QPen>
#include <string>
#include <cmath>
#include <vector>
const double PI = 3.14;

class Shape
{
public:
    Shape(int shapeId,
          std::string shapeType,
          int x,
          int y,
          Qt::GlobalColor penColor,
          int penWidth,
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
          brushStyle{brushStyle} {}

    virtual ~Shape() {}

    virtual void Draw() = 0;
    virtual void Move(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    int getX() {return x;}
    int getY() {return y;}

    virtual int Perimeter() { return 0; }
    virtual int Area()      { return 0; }

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
};

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

private:
    std::vector<int> points;
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

    double Perimeter() override { for (int i = 0; i < points.size(); i ++){ points[i][i] + points[i+1][i+1]};}

private:
        std::vector < vector<int> > points;
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
};

#endif // SHAPE_H
