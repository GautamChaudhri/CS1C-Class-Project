#ifndef SHAPE_H
#define SHAPE_H

#include <QColor>
#include <QFont>

using namespace std;


class Shape
{
public:
    Shape(int shapeId,
        string shapeType,
        int x1,
        int y1,
        Qt::GlobalColor penColor,
        int penWidth,
        Qt::PenStyle penStyle,
        Qt::PenCapStyle penCapStyle,
        Qt::PenJoinStyle penJoinStyle)
        : shapeId{shapeId},
        shapeType{shapeType},
        x1{x1},
        y1{y1},
        penColor{penColor},
        penWidth{penWidth},
        penStyle{penStyle},
        penCapStyle{penCapStyle},
        penJoinStyle{penJoinStyle}
    {}

    Shape(int shapeId,
        string shapeType,
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
        brushStyle{brushStyle}
    {}

    Shape(int shapeId,
        string shapeType,
        int x1,
        int y1,
        string textString,
        Qt::GlobalColor textColor,
        Qt::AlignmentFlag textAlignment,
        int textPointSize,
        string textFontFamily,
        QFont::Style textFontStyle,
        QFont::Weight textFontWeight)
        : shapeId{shapeId},
        shapeType{shapeType},
        x1{x1},
        y1{y1},
        textString{textString},
        textColor{textColor},
        textAlignment{textAlignment},
        textPointSize{textPointSize},
        textFontFamily{textFontFamily},
        textFontStyle{textFontStyle},
        textFontWeight{textFontWeight}
    {}

    virtual ~Shape() {}

    virtual void Draw() {}
    virtual void Move(int x1, int y1)
    {
        this->x1 = x1;
        this->y1 = y1;
    }

    virtual int Perimeter() { return x1 + y1; }
    virtual int Area() {return x1 * y1; }

private:
    int    shapeId;
    string shapeType;

    int x1;
    int y1;

    Qt::GlobalColor   penColor;
    int               penWidth;
    Qt::PenStyle      penStyle;
    Qt::PenCapStyle   penCapStyle;
    Qt::PenJoinStyle  penJoinStyle;
    Qt::GlobalColor   brushColor;
    Qt::BrushStyle    brushStyle;
    string            textString;
    Qt::GlobalColor   textColor;
    Qt::AlignmentFlag textAlignment;
    int               textPointSize;
    string            textFontFamily;
    QFont::Style      textFontStyle;
    QFont::Weight     textFontWeight;
};


class Line : public Shape
{
public:
    Line(int shapeId, string shapeType, int x1, int y1,
         Qt::GlobalColor penColor, int penWidth, Qt::PenStyle penStyle,
         Qt::PenCapStyle penCapStyle, Qt::PenJoinStyle penJoinStyle, int x2, int y2)
        : Shape(shapeId, shapeType, x1, y1, penColor, penWidth, penStyle, penCapStyle, penJoinStyle), x2{x2}, y2{y2} {}

private:
    int x2;
    int y2;

};


class Polyline : public Shape
{
public:
    Polyline(int shapeId, string shapeType, int x1, int y1,
         Qt::GlobalColor penColor, int penWidth, Qt::PenStyle penStyle,
         Qt::PenCapStyle penCapStyle, Qt::PenJoinStyle penJoinStyle, int x2, int y2, int x3, int y3 )
        : Shape(shapeId, shapeType, x1, y1, penColor, penWidth, penStyle, penCapStyle, penJoinStyle), x2{x2}, y2{y2},x3{x3}, y3{y3}  {}

private:
    int x2;
    int y2;
    int x3;
    int y3;

};


class Polygon : public Shape
{
public:
    Polygon(int shapeId, string shapeType, int x1, int y1,
        Qt::GlobalColor penColor, int penWidth, Qt::PenStyle penStyle,
         Qt::PenCapStyle penCapStyle, Qt::PenJoinStyle penJoinStyle, int x2, int y2, int x3, int y3 )
        : Shape(shapeId, shapeType, x1, y1, penColor, penWidth, penStyle, penCapStyle, penJoinStyle, brushColor, brushStyle), x2{x2}, y2{y2},x3{x3}, y3{y3}  {}

private:
    int x2;
    int y2;
    int x3;
    int y3;
};


class Rectangle : public Shape
{
public:
    Rectangle(int shapeId, string shapeType, int x1, int y1,
    Qt::GlobalColor penColor, int penWidth, Qt::PenStyle penStyle,
    Qt::PenCapStyle penCapStyle, Qt::PenJoinStyle penJoinStyle, int length, int width)
    : Shape(shapeId, shapeType, x1, y1, penColor, penWidth, penStyle, penCapStyle,penJoinStyle, penCapStyle, penJoinStyle), length{length}, width{width} {}

private:
    int length;
    int width;
};


class Square : public Shape
{
public:
    Square(int shapeId, string shapeType, int x1, int y1,
        Qt::GlobalColor penColor, int penWidth, Qt::PenStyle penStyle,
        Qt::PenCapStyle penCapStyle, Qt::PenJoinStyle penJoinStyle, int length)
        : Shape(shapeId, shapeType, x1, y1, penColor, penWidth, penStyle, penCapStyle,penJoinStyle, penCapStyle, penJoinStyle), length{length} {}
private:
    int length;
};


class Ellipse : public Shape
{
public:
    Ellipse(int shapeId, string shapeType, int x1, int y1,
    Qt::GlobalColor penColor, int penWidth, Qt::PenStyle penStyle,
    Qt::PenCapStyle penCapStyle, Qt::PenJoinStyle penJoinStyle, int a, int b)
    : Shape(shapeId, shapeType, x1, y1, penColor, penWidth, penStyle, penCapStyle,penJoinStyle, penCapStyle, penJoinStyle), a{a}, b{b} {}

private:
    int a;
    int b;
};


class Circle : public Shape
{
public:
    Circle(int shapeId, string shapeType, int x1, int y1,
    Qt::GlobalColor penColor, int penWidth, Qt::PenStyle penStyle,
    Qt::PenCapStyle penCapStyle, Qt::PenJoinStyle penJoinStyle, int r)
    : Shape(shapeId, shapeType, x1, y1, penColor, penWidth, penStyle, penCapStyle,penJoinStyle, penCapStyle, penJoinStyle), r{r} {}

private:
    int r;
};


class Text : public Shape
{
public:
    Text(int shapeId,
         string shapeType,
         int x1,
         int y1,
         string textString,
         Qt::GlobalColor textColor,
         Qt::AlignmentFlag textAlignment,
         int textPointSize,
         string textFontFamily,
         QFont::Style textFontStyle,
         QFont::Weight textFontWeight,
         int length,
         int width)
        : Shape(shapeId, shapeType, x1, y1, textString, textColor, textAlignment, textPointSize, textFontFamily, textFontStyle,textFontWeight), length{length}, width{width} {}
private:
    int length;
    int width;
};

#endif // SHAPE_H
