#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {}

void RenderArea::setShapes(const alpha::vector<Shape*>& shapes) {
    renderShapes = std::move(shapes); // moves the local copy
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    int vecSize;
    vecSize = renderShapes.size();

    for(int i = 0; i < vecSize; ++i)
    {
        renderShapes[i]->Draw(this);
    }
}
