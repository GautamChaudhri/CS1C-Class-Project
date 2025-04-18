#pragma once

#include <QWidget>
#include <QPainter>
#include <QPen>

#include "all_shapes.h"
#include <QMouseEvent>

class RenderArea : public QWidget
{
public:
    RenderArea(QWidget *parent = nullptr);

    void setShapes(const alpha::vector<Shape*>& shapes);

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    alpha::vector<Shape*> renderShapes;
};
