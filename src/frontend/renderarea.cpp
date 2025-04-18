#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {}

void RenderArea::setShapes(const alpha::vector<Shape*>& shapes)
{
    renderShapes = std::move(shapes); // moves the local copy
}

void RenderArea::mousePressEvent(QMouseEvent* event)
{
    QPoint clickPoint = event->pos();
    int vecSize = renderShapes.size();
    int newSelectionIndex = -1;

    for (int i = 0; i < vecSize; ++i)
    {
        if (renderShapes[i]->isPointInside(clickPoint))
        {
            newSelectionIndex = i; // Mark the new selected shape index
        }
    }

    // Update selection state
    if (newSelectionIndex != shapeSelectedIndex)
    {
        if (shapeSelectedIndex >= 0 && shapeSelectedIndex < vecSize)
        {
            renderShapes[shapeSelectedIndex]->setSelected(false); // Deselect previous
        }
        shapeSelectedIndex = newSelectionIndex;
        if (shapeSelectedIndex >= 0 && shapeSelectedIndex < vecSize)
        {
            renderShapes[shapeSelectedIndex]->setSelected(true); // Select new shape
        }
    }

    update(); // Trigger repaint to show the selection state visually
}

void RenderArea::mouseMoveEvent(QMouseEvent* event)
{
    if (shapeSelectedIndex >= 0 && shapeSelectedIndex < renderShapes.size())
    {
        QPoint newPos = mapFromGlobal(QCursor::pos());

        // Get the current position of the selected shape
        QPoint currentPos = renderShapes[shapeSelectedIndex]->getPoints();

        // Only update if the new position is different from the current position
        if (newPos != currentPos)
        {
            renderShapes[shapeSelectedIndex]->Move(newPos.x(), newPos.y());
            update(); // Trigger repaint
        }
    }
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
