#ifndef SHAPE_H
#define SHAPE_H

#include <qcolor>
#include <qfont>
using namespace std;


class Shape
{
public:
    Shape(int shapeId, string shapeType, int x1, int y1,
          Qt::GlobalColor penColor, int penWidth, Qt::PenStyle penStyle,
          Qt::PenCapStyle penCapStyle, Qt::PenJoinStyle penJoinStyle) {}
    virtual ~Shape() {}

    virtual void Draw() {}
    virtual void Move(int x1, int y1)
    {
        this->x1 = x1;
        this->y1 = y1;
    }

    virtual double Perimeter() { return x1 + y1; }
    virtual double Area() {return x1 * y1; }

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

private:
    int x3;
    int y3;

};


class Polygon : public Shape
{
public:

private:

};


class Rectangle : public Shape
{
public:

private:
    double length;
    double width;
};


class Square : public Shape
{
public:

private:
    double length;
};


class Ellipse : public Shape
{
public:

private:
    double a;
    double b;
};


class Circle : public Shape
{
public:

private:
    double r;
};


class Text : public Shape
{
public:

private:
    int length;
    int width;
};





















#endif // SHAPE_H
