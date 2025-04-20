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
    void addShape(Shape* shape)
    {
        renderShapes.push_back(shape);
    }

    const alpha::vector<Shape*>& getShapes() const
    {
        return renderShapes;
    }

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    alpha::vector<Shape*> renderShapes;
    int shapeSelectedIndex; // This is the vector index of the current shape selected, this is done so we prevent multiple shapes being selected at once
};
