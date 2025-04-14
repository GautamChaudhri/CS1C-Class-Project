#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {}

void RenderArea::paintEvent(QPaintEvent *event)
{
    // TEST
    QPoint coords(500, 500);
    QBrush brush(Qt::blue);
    QPen pen(Qt::blue);

    std::unique_ptr<Shape> shape = std::make_unique<Square>(1, "Square", coords, pen, brush, 50);
    addShape(std::move(shape));

    int vecSize;
    vecSize = renderShapes.size();

    for(int i = 0; i < vecSize; ++i)
    {
        renderShapes[i]->Draw(this);
    }
}
