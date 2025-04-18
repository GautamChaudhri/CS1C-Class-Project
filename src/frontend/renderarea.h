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

    void mousePressEvent(QMouseEvent* event)
    {
        int vecSize = renderShapes.size();

        QPoint clickPoint = event->pos();

        for (int i = 0; i < vecSize; ++i)
        {
            if (renderShapes[i]->isPointInside(clickPoint))
            {
                renderShapes[i]->setSelected(true);
            } else
            {
                renderShapes[i]->setSelected(false);
            }
        }
        update(); // Trigger repaint to show the selection state visually
    }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    alpha::vector<Shape*> renderShapes;
};
