#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent), shapeSelectedIndex{-1} {}

void RenderArea::setRenderShapes(const alpha::vector<Shape*>* renderShapes) {
    this->renderShapes = renderShapes;
}

void RenderArea::mousePressEvent(QMouseEvent* event)
{
    QPoint clickPoint = event->pos();
    int vecSize = renderShapes->size();
    int newSelectionIndex = -1;

    for (int i = 0; i < vecSize; ++i)
    {
        if ((*renderShapes)[i]->isPointInside(clickPoint))
        {
            newSelectionIndex = i; // Mark the new selected shape index
        }
    }

    // Update selection state
    if (newSelectionIndex != shapeSelectedIndex)
    {
        if (shapeSelectedIndex >= 0 && shapeSelectedIndex < vecSize)
        {
            (*renderShapes)[shapeSelectedIndex]->setSelected(false); // Deselect previous
        }

        shapeSelectedIndex = newSelectionIndex;

        if (shapeSelectedIndex >= 0 && shapeSelectedIndex < vecSize)
        {
            (*renderShapes)[shapeSelectedIndex]->setSelected(true); // Select new shape
        }
    }

    update(); // Trigger repaint to show the selection state visually
}

void RenderArea::mouseMoveEvent(QMouseEvent* event)
{
    if (shapeSelectedIndex >= 0 && shapeSelectedIndex < renderShapes->size())
    {
        QPoint newPos = mapFromGlobal(QCursor::pos());

        // Get the current position of the selected shape
        QPoint currentPos = (*renderShapes)[shapeSelectedIndex]->getPoints();

        // Only update if the new position is different from the current position
        if (newPos != currentPos)
        {
            (*renderShapes)[shapeSelectedIndex]->Move(newPos.x(), newPos.y());
            update(); // Trigger repaint
        }
    }
}

void RenderArea::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (shapeSelectedIndex >= 0 && shapeSelectedIndex < renderShapes->size())
    {
        switch((*renderShapes)[shapeSelectedIndex]->getShapeId())
        {
        case 1: // Line

            break;

        case 2: // Polyline
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:

            break;

        case 6:

            break;

        case 7:

            break;

        case 8:

            break;
        }
    }

    update();
}

void RenderArea::resetSelection()
{
    int vecSize = renderShapes->size();

    for (int i = 0; i < vecSize; ++i)
    {
        (*renderShapes)[i]->setSelected(false);
    }

    shapeSelectedIndex = -1;
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    int vecSize;
    vecSize = renderShapes->size();

    //emit initializeTreeWidget(); //Bad for performance but will fix later

    for(int i = 0; i < vecSize; ++i)
    {
        (*renderShapes)[i]->Draw(this);
    }
}

void RenderArea::setShapeSelectedIndex(int newIndex)
{
    shapeSelectedIndex = newIndex;
}

int RenderArea::getShapeSelected() const
{
    if(shapeSelectedIndex < 0)
    {
        return -1;
    }

    return (*renderShapes)[shapeSelectedIndex]->getTrackerId();
}

int RenderArea::getShapeSelectedIndex() const
{
    return shapeSelectedIndex;
}

