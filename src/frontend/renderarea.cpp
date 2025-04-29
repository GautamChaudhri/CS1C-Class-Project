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
        Shape* shape = (*renderShapes)[shapeSelectedIndex];
        QPoint newPos = mapFromGlobal(QCursor::pos());

        // Only update if the new position is different from the current position
        if (newPos != shape->getPoints())
        {
            shape->Move(newPos.x(), newPos.y());
            update(); // Trigger repaint
        }
    }
}


void RenderArea::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (shapeSelectedIndex >= 0 && shapeSelectedIndex < renderShapes->size())
    {
        (*renderShapes)[shapeSelectedIndex]->getParentItem()->setExpanded(true);
    }
}

void RenderArea::mouseReleaseEvent(QMouseEvent* event)
{
    if (shapeSelectedIndex < 0 || shapeSelectedIndex >= renderShapes->size())
    {
        // Validate the shapeSelectedIndex
        return;
    }

    Shape* shape = (*renderShapes)[shapeSelectedIndex];
    if (!shape)
    {
        // Check if the shape pointer is null
        return;
    }

    QPoint newPos = mapFromGlobal(QCursor::pos());

    // Update display coordinates
    updateShapeDisplayCoords(shape, newPos);
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

void RenderArea::updateShapeDisplayCoords(Shape* item, const QPoint& position) const
{
    auto children = item->getChildItems();
    QString xStr = QString::number(position.x());
    QString yStr = QString::number(position.y());
    children[3]->setText(1, xStr);
    children[4]->setText(1, yStr);
}


