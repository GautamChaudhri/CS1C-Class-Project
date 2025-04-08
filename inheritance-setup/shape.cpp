#include "shape.h"

/****************************************************
* class Shape - Abstract Base Class
*****************************************************/

Shape::Shape(int          shapeId,
             std::string       shapeType,
             int          x,
             int          y,
             Qt::GlobalColor  penColor,
             int          penWidth,
             Qt::PenStyle     penStyle,
             Qt::PenCapStyle  penCapStyle,
             Qt::PenJoinStyle penJoinStyle,
             Qt::GlobalColor  brushColor,
             Qt::BrushStyle   brushStyle)
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
    brushStyle{brushStyle}
{}

virtual Shape::~Shape()
{}

void Shape::Move(int x, int y)
{
    this->x = x;
    this->y = y;
}

/**************** ACCESSOR FUNCTIONS ****************/
int    Shape::getShapeId()   const { return shapeId; }
int    Shape::getTrackerId() const { return trackerId; }
string Shape::getShapeType() const { return shapeType; }

int Shape::getX() const { return X; }
int Shape::getY() const { return Y; }

Qt::GlobalColor  Shape::getGlobalColor()  const { return globalColor; }
int              Shape::getPenWidth()     const { return penWidth; }
Qt::PenStyle     Shape::getPenStyle()     const { return penStyle; }
Qt::PenCapStyle  Shape::getPenCapStyle()  const { return penCapStyle; }
Qt::PenJoinStyle Shape::getPenJoinStyle() const { return penJoinStyle; }
Qt::GlobalColor  Shape::getBrushColor()   const { return brushColor; }
Qt::BrushStyle   Shape::getBrushStyle()   const { return brushStyle; }
/****************************************************/

/***************** MUTATOR FUNCTIONS ****************/
int    Shape::setShapeId(int shapeId)        { this->shapeId   = shapeId; }
int    Shape::setTrackerId(int trackerId)    { this->trackerId = trackerId; }
string Shape::setShapeType(string shapeType) { this->shapeType = shapeType; }

int Shape::setX(int x) { this->x = x; }
int Shape::setY(int y) { this->y = y; }

Qt::GlobalColor  Shape::setGlobalColor(Qt::GlobalColor globalColor)    { this->globalColor  = globalColor; }
int              Shape::setPenWidth(int penWidth)                      { this->penWidth     = penwidth; }
Qt::PenStyle     Shape::setPenStyle(Qt::PenStyle penStyle)             { this->penStyle     = penStyle; }
Qt::PenCapStyle  Shape::setPenCapStyle(Qt::PenCapStyle penCapStyle)    { this->penCapStyle  = penCapStyle; }
Qt::PenJoinStyle Shape::setPenJoinStyle(Qt::PenJoinStyle penJoinStyle) { this->penJoinStyle = penJoinStyle; }
Qt::GlobalColor  Shape::setBrushColor(Qt::GlobalColor brushColor)      { this->brushColor   = brushColor; }
Qt::BrushStyle   Shape::setBrushStyle(Qt::BrushStyle brushStyle)       { this->brushStyle   = brushStyle; }
/****************************************************/

// Overloaded Operators
bool operator==(const Shape& shape1, const Shape& shape2)
{
    return shape1.shapeId == shape2.shapeId;
}

bool operator<(const Shape& shape1, const Shape& shape2)
{
    return shape1.shapeId < shape2.shapeId;
}

/****************************************************/


/****************************************************
* class Line - Derived Class
*****************************************************/

Line::Line(int          shapeId,
           std::string       shapeType,
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
           int          y2)
    : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle,
            penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
    x1{x1},
    y1{y1},
    x2{x2},
    y2{y2}
{}

double Line::Perimeter() const
{
    return sqrt(pow((x1 - x2),2) + pow((y1 - y2), 2));
}

/****************************************************/


/****************************************************
* class Polyline - Derived Class
*****************************************************/

Polyline::Polyline(int          shapeId,
                   std::string       shapeType,
                   int          x,
                   int          y,
                   Qt::GlobalColor  penColor,
                   int          penWidth,
                   Qt::PenStyle     penStyle,
                   Qt::PenCapStyle  penCapStyle,
                   Qt::PenJoinStyle penJoinStyle,
                   std::vector<int>  points)
    : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle,
            penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
    points{points}
{}

double Polyline::Perimeter() const
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

/****************************************************/



/****************************************************
* class Polygon - Derived Class
*****************************************************/

Polygon::Polygon(int shapeId,
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
    : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle,
            penCapStyle, penJoinStyle, brushColor, brushStyle),
    points{points}
{}

double Polygon::Perimeter() const
{
    double perimeter;

    perimeter = sqrt(pow((points[0][0] - points[1][0]), 2) + pow((points[0][1] - points[1][1]), 2) * points.size());

    return perimeter;
}

double Polygon::Area() const
{
    double apothem;

    apothem = (sqrt(pow((points[0][0] - points[1][0]), 2) + pow((points[0][1] - points[1][1]), 2))) / tan(180 / points.size());

    return (Perimeter() * apothem) / 2;
}

/****************************************************/


/****************************************************
* class Rectangle - Derived Class
*****************************************************/

Rectangle::Rectangle(int          shapeId,
                     std::string       shapeType,
                     int          x,
                     int          y,
                     Qt::GlobalColor  penColor,
                     int          penWidth,
                     Qt::PenStyle     penStyle,
                     Qt::PenCapStyle  penCapStyle,
                     Qt::PenJoinStyle penJoinStyle,
                     int          length,
                     int          width)
    : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle,
            penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
    length{length},
    width{width}
{}


double Rectangle::Perimeter() const { return (length * 2) + (width * 2); }
double Rectangle::Area()      const { return length * width; }

/****************************************************/


/****************************************************
* class Square - Derived Class
*****************************************************/

Square::Square(int          shapeId,
               std::string       shapeType,
               int          x,
               int          y,
               Qt::GlobalColor  penColor,
               int          penWidth,
               Qt::PenStyle     penStyle,
               Qt::PenCapStyle  penCapStyle,
               Qt::PenJoinStyle penJoinStyle,
               int          length)
    : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle,
            penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
    length{length}
{}


double Square::Perimeter() const { return length * 4; }
double Square::Area()      const { return pow(length, 2); }

/****************************************************/


/****************************************************
* class Ellipse - Derived Class
*****************************************************/

Ellipse::Ellipse(int shapeId,
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
    : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle,
            penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
    a{a},
    b{b}
{}

double Ellipse::Perimeter() const { return 2 * PI * sqrt((pow((2 * a), 2) + pow((2 * b), 2)) / 2); }
double Ellipse::Area()      const { return PI * a * b; }

/****************************************************/


/****************************************************
* class Circle - Derived Class
*****************************************************/

Circle::Circle(int         shapeId,
               std::string       shapeType,
               int          x,
               int          y,
               Qt::GlobalColor  penColor,
               int          penWidth,
               Qt::PenStyle     penStyle,
               Qt::PenCapStyle  penCapStyle,
               Qt::PenJoinStyle penJoinStyle,
               int          r)
    : Shape(shapeId, shapeType, x, y, penColor, penWidth, penStyle,
            penCapStyle, penJoinStyle, Qt::GlobalColor(), Qt::BrushStyle()),
    r{r}
{}

double Circle::Perimeter() const { return 2 * PI * r; }
double Circle::Area()      const { return PI * pow(r, 2); }

/****************************************************/


/****************************************************
* class Text - Derived Class
*****************************************************/

Text::Text(int           shapeId,
           std::string        shapeType,
           int           x,
           int           y,
           std::string        textString,
           Qt::GlobalColor   textColor,
           Qt::AlignmentFlag textAlignment,
           int           textPointSize,
           std::string        textFontFamily,
           QFont::Style         textFontStyle,
           QFont::Weight        textFontWeight,
           int           length,
           int           width)
    : Shape(shapeId, shapeType, x, y, Qt::GlobalColor(), 0, Qt::PenStyle(), Qt::PenCapStyle(),
            Qt::PenJoinStyle(), Qt::GlobalColor(), Qt::BrushStyle()),
    textString{textString},
    textColor{textColor},
    textAlignment{textAlignment},
    textPointSize{textPointSize},
    textFontFamily{textFontFamily},
    textFontStyle{textFontStyle},
    textFontWeight{textFontWeight},
    length{length},
    width{width}
{}

double Text::Perimeter() const { return (length * 2) + (width * 2); }
double Text::Area()      const { return length * width; }

/****************************************************/
