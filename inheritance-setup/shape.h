#ifndef SHAPE_H
#define SHAPE_H

#include <QColor>
#include <QFont>
#include <QPen>
#include <string>

class Shape
{
public:
    Shape(int shapeId,
          std::string shapeType,
          int x1,
          int y1,
          Qt::GlobalColor penColor,
          int penWidth,
          Qt::PenStyle penStyle,
          Qt::PenCapStyle penCapStyle,
          Qt::PenJoinStyle penJoinStyle,
          Qt::GlobalColor brushColor,
          Qt::BrushStyle brushStyle)
        : shapeId{shapeId},
          shapeType{shapeType},
          x1{x1},
          y1{y1},
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
        x1 = x;
        y1 = y;
    }

    virtual int Perimeter() { return x1 + y1; }
    virtual int Area()      { return x1 * y1; }

protected:
    int shapeId;
    std::string shapeType;

    int x1;
    int y1;

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
         int x1,
         int y1,
         Qt::GlobalColor penColor,
         int penWidth,
         Qt::PenStyle penStyle,
         Qt::PenCapStyle penCapStyle,
         Qt::PenJoinStyle penJoinStyle,
         int x2,
         int y2)
       : Shape(shapeId, shapeType, x1, y1, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
         x2{x2},
         y2{y2} {}

private:
    int x2;
    int y2;
};

class Polyline : public Shape
{
public:
    Polyline(int shapeId,
             std::string shapeType,
             int x1,
             int y1,
             Qt::GlobalColor penColor,
             int penWidth,
             Qt::PenStyle penStyle,
             Qt::PenCapStyle penCapStyle,
             Qt::PenJoinStyle penJoinStyle,
             int x2,
             int y2,
             int x3,
             int y3)
           : Shape(shapeId, shapeType, x1, y1, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
            x2{x2},
            y2{y2},
            x3{x3},
            y3{y3} {}

private:
    int x2, y2, x3, y3;
};

class Polygon : public Shape
{
public:
    Polygon(int shapeId,
            std::string shapeType,
            int x1,
            int y1,
            Qt::GlobalColor penColor,
            int penWidth,
            Qt::PenStyle penStyle,
            Qt::PenCapStyle penCapStyle,
            Qt::PenJoinStyle penJoinStyle,
            Qt::GlobalColor brushColor,
            Qt::BrushStyle brushStyle,
            int x2,
            int y2,
            int x3,
            int y3)
          : Shape(shapeId, shapeType, x1, y1, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, brushColor, brushStyle),
            x2{x2},
            y2{y2},
            x3{x3},
            y3{y3} {}

private:
    int x2, y2, x3, y3;
};

class Rectangle : public Shape
{
public:
    Rectangle(int shapeId,
              std::string shapeType,
              int x1,
              int y1,
              Qt::GlobalColor penColor,
              int penWidth,
              Qt::PenStyle penStyle,
              Qt::PenCapStyle penCapStyle,
              Qt::PenJoinStyle penJoinStyle,
              int length,
              int width)
            : Shape(shapeId, shapeType, x1, y1, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
              length{length},
              width{width} {}

private:
    int length;
    int width;
};

class Square : public Shape
{
public:
    Square(int shapeId,
           std::string shapeType,
           int x1,
           int y1,
           Qt::GlobalColor penColor,
           int penWidth,
           Qt::PenStyle penStyle,
           Qt::PenCapStyle penCapStyle,
           Qt::PenJoinStyle penJoinStyle,
           int length)
         : Shape(shapeId, shapeType, x1, y1, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
           length{length} {}

private:
    int length;
};

class Ellipse : public Shape
{
public:
    Ellipse(int shapeId,
            std::string shapeType,
            int x1,
            int y1,
            Qt::GlobalColor penColor,
            int penWidth,
            Qt::PenStyle penStyle,
            Qt::PenCapStyle penCapStyle,
            Qt::PenJoinStyle penJoinStyle,
            int a,
            int b)
          : Shape(shapeId, shapeType, x1, y1, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
            a{a},
            b{b} {}

private:
    int a, b;
};

class Circle : public Shape
{
public:
    Circle(int shapeId,
           std::string shapeType,
           int x1,
           int y1,
           Qt::GlobalColor penColor,
           int penWidth,
           Qt::PenStyle penStyle,
           Qt::PenCapStyle penCapStyle,
           Qt::PenJoinStyle penJoinStyle,
           int r)
         : Shape(shapeId, shapeType, x1, y1, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
           r{r} {}

private:
    int r;
};

class Text : public Shape
{
public:
    Text(int shapeId,
         std::string shapeType,
         int x1,
         int y1,
         std::string textString,
         Qt::GlobalColor textColor,
         Qt::AlignmentFlag textAlignment,
         int textPointSize,
         std::string textFontFamily,
         QFont::Style textFontStyle,
         QFont::Weight textFontWeight,
         int length,
         int width)
        : Shape(shapeId, shapeType, x1, y1, Qt::GlobalColor(), 0, Qt::PenStyle(), Qt::PenCapStyle(), Qt::PenJoinStyle(), Qt::GlobalColor(), Qt::BrushStyle()),
          textString{textString},
          textColor{textColor},
          textAlignment{textAlignment},
          textPointSize{textPointSize},
          textFontFamily{textFontFamily},
          textFontStyle{textFontStyle},
          textFontWeight{textFontWeight},
          length{length},
          width{width} {}

private:
    int length, width;
    std::string textString;
    Qt::GlobalColor textColor;
    Qt::AlignmentFlag textAlignment;
    int textPointSize;
    std::string textFontFamily;
    QFont::Style textFontStyle;
    QFont::Weight textFontWeight;
};

#endif // SHAPE_H
