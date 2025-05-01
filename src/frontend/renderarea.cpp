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
    // If dropdown is not expanded, expand it; If dropdown is expanded, close it
    if (shapeSelectedIndex >= 0 && shapeSelectedIndex < renderShapes->size())
    {
        if ((*renderShapes)[shapeSelectedIndex]->getParentItem()->isExpanded() == false)
        {
            (*renderShapes)[shapeSelectedIndex]->getParentItem()->setExpanded(true);
        }
        else
        {
            (*renderShapes)[shapeSelectedIndex]->getParentItem()->setExpanded(false);
        }
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

const alpha::vector<Shape*>& RenderArea::getShapes() const
{
    return *renderShapes;
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
    auto pointsChildren = item->getPointsItems();

    const int pointsChildrenSize = pointsChildren.size();

    QString xStr = QString::number(position.x());
    QString yStr = QString::number(position.y());

    // Setting new X and Y Coords
    for (int i = 0; i < children.size(); ++i)
    {
        if (children[i]->text(0).startsWith("X"))
        {
            children[i]->setText(1, xStr);
        }
        else if (children[i]->text(0).startsWith("Y"))
        {
            children[i]->setText(1, yStr);
        }
    }

    // Setting new points coords
    switch (item->getShapeId())
    {
        case LINE:
        {
            Line* line = static_cast<Line*>(item);

            QString xStartPointStr = QString::number(line->getStartPoint().x());
            QString yStartPointStr = QString::number(line->getStartPoint().y());

            QString xEndPointStr = QString::number(line->getEndPoint().x());
            QString yEndPointStr = QString::number(line->getEndPoint().y());

            pointsChildren[0]->setText(1, xStartPointStr);
            pointsChildren[1]->setText(1, yStartPointStr);

            pointsChildren[2]->setText(1, xEndPointStr);
            pointsChildren[3]->setText(1, yEndPointStr);

            break;
        }

        case POLYLINE:
        {
            Polyline* polyline = static_cast<Polyline*>(item);

            const QPolygon pointsList = polyline->getPointsList();
            const int pointsListSize  = pointsList.size();

            alpha::vector<QString> coordStrings;

            for (int i = 0; i < pointsListSize; ++i)
            {
                coordStrings.push_back(QString::number(pointsList[i].x()));
                coordStrings.push_back(QString::number(pointsList[i].y()));
            }

            for (int i = 0; i < pointsChildrenSize; ++i)
            {
                pointsChildren[i]->setText(1, coordStrings[i]);
            }

            break;
        }

        case POLYGON:
        {
            Polygon* polygon = static_cast<Polygon*>(item);

            const QPolygon pointsList = polygon->getPointsList();
            const int pointsListSize  = pointsList.size();

            alpha::vector<QString> coordStrings;

            for (int i = 0; i < pointsListSize; ++i)
            {
                coordStrings.push_back(QString::number(pointsList[i].x()));
                coordStrings.push_back(QString::number(pointsList[i].y()));
            }

            for (int i = 0; i < pointsChildrenSize; ++i)
            {
                pointsChildren[i]->setText(1, coordStrings[i]);
            }

            break;
        }
    }

    //children[2]->setText(1, xStr);
    //children[3]->setText(1, yStr);
}


