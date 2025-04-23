#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {}

void RenderArea::setShapes(const alpha::vector<Shape*>& shapes)
{
    renderShapes = shapes; // copy the shapes from pointer
}

void RenderArea::setShapes2(const alpha::vector<Shape*>* shapes)
{
    renderShapes = *shapes; // copy the shapes from pointer
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

void RenderArea::onRenderAreaChanged() {
    update();
}

void RenderArea::onRenderAreaNotChanged(const QString& message) {
    // handle error: you could show a popup or log the message
}

void RenderArea::showStatusMessage(QString message)
{
    qDebug() << "Status:" << message;
}