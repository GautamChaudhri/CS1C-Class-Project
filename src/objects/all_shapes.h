// all_shapes.h | Include this file to automatically include all of these shapes in one line
#ifndef ALL_SHAPES_H
#define ALL_SHAPES_H

#include "circle.h"
#include "ellipse.h"
#include "line.h"
#include "polygon.h"
#include "polyline.h"
#include "rectangle.h"
#include "shape.h"
#include "square.h"
#include "text.h"

enum ShapeIDs {LINE = 1, POLYLINE, POLYGON, RECTANGLE, SQUARE, ELLIPSE, CIRCLE, TEXT};

#endif // ALL_SHAPES_H