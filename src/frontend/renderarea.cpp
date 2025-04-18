#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {}

void RenderArea::setShapes(const alpha::vector<Shape*>& shapes)
{
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


void RenderArea::mousePressEvent(QMouseEvent* event)
{
    QPoint clickPoint = event->pos();

    int vecSize = renderShapes.size();

    for (int i = 0; i < vecSize; ++i)
    {
        if (renderShapes[i]->isPointInside(clickPoint))
        {
            renderShapes[i]->setSelected(true);
        }
        else
        {
            renderShapes[i]->setSelected(false);
        }
    }
    update(); // Trigger repaint to show the selection state visually
}


void RenderArea::mouseMoveEvent(QMouseEvent* event)
{
    QPoint oldPos;
    QPoint newPos;

    int vecSize = renderShapes.size();

    for (int i = 0; i < vecSize; ++i)
    {
        if (renderShapes[i]->getSelected() == true)
        {
            oldPos = renderShapes[i]->getPoints();

            newPos = QCursor::pos(); // Recieves the position of the mouse

            renderShapes[i]->Move(newPos.x(), newPos.y()); // Moves the shape coords to the X and Y coords of the mouse
        }
    }

    update();
}
