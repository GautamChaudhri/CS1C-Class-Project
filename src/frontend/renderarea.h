#pragma once

#include <QWidget>
#include <QPainter>
#include <QPen>

#include "all_shapes.h"

class RenderArea : public QWidget
{
public:
    RenderArea(QWidget *parent = nullptr);

    void setShapes(const alpha::vector<Shape*>& shapes);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    alpha::vector<Shape*> renderShapes;
};
