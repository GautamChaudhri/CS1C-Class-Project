#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {}

void RenderArea::setShapes2(const alpha::vector<Shape*>& shapes)
{
    renderShapes2 = shapes; // copy the shapes from pointer
}

void RenderArea::setShapes(const alpha::vector<Shape*>* shapes)
{
    allShapes = shapes; // copy the shapes from pointer
}

void RenderArea::setRenderShapes(const alpha::vector<Shape*>* renderShapes) {
    this->renderShapes = renderShapes;
}

void RenderArea::mousePressEvent(QMouseEvent* event)
{
    QPoint clickPoint = event->pos();
    int vecSize = renderShapes2.size();
    int newSelectionIndex = -1;

    for (int i = 0; i < vecSize; ++i)
    {
        if (renderShapes2[i]->isPointInside(clickPoint))
        {
            newSelectionIndex = i; // Mark the new selected shape index
        }
    }

    // Update selection state
    if (newSelectionIndex != shapeSelectedIndex)
    {
        if (shapeSelectedIndex >= 0 && shapeSelectedIndex < vecSize)
        {
            renderShapes2[shapeSelectedIndex]->setSelected(false); // Deselect previous
        }
        shapeSelectedIndex = newSelectionIndex;
        if (shapeSelectedIndex >= 0 && shapeSelectedIndex < vecSize)
        {
            renderShapes2[shapeSelectedIndex]->setSelected(true); // Select new shape
        }
    }

    update(); // Trigger repaint to show the selection state visually
}

void RenderArea::mouseMoveEvent(QMouseEvent* event)
{
    if (shapeSelectedIndex >= 0 && shapeSelectedIndex < renderShapes2.size())
    {
        QPoint newPos = mapFromGlobal(QCursor::pos());

        // Get the current position of the selected shape
        QPoint currentPos = renderShapes2[shapeSelectedIndex]->getPoints();

        // Only update if the new position is different from the current position
        if (newPos != currentPos)
        {
            renderShapes2[shapeSelectedIndex]->Move(newPos.x(), newPos.y());
            update(); // Trigger repaint
        }
    }
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    int vecSize;
    vecSize = renderShapes2.size();

    for(int i = 0; i < vecSize; ++i)
    {
        renderShapes2[i]->Draw(this);
    }
}
