#pragma once

#include <QWidget>
#include <QPainter>
#include <QPen>

#include "shape.h"
#include "line.h"
#include "polyline.h"
#include "polygon.h"
#include "rectangle.h"
#include "square.h"
#include "ellipse.h"
#include "circle.h"
#include "text.h"

#include "vector.h"

class RenderArea : public QWidget
{
public:
    RenderArea(QWidget *parent = nullptr);

    void addShape(std::unique_ptr<Shape> newShape)
    {
        renderShapes.push_back(std::move(newShape));
    }

protected:
    void paintEvent(QPaintEvent *event);

private:
    std::vector<std::unique_ptr<Shape>> renderShapes;
};
