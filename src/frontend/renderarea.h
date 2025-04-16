#pragma once

#include <QWidget>
#include <QPainter>
#include <QPen>

#include "all_shapes.h"

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
