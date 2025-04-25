#pragma once

#include <QWidget>
#include <QPainter>
#include <QPen>

#include "../objects/all_shapes.h"
#include "../objects/vector.h"
#include <QMouseEvent>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(QWidget *parent = nullptr);
    void setRenderShapes(const alpha::vector<Shape*>* renderShapes);

    const alpha::vector<Shape*>& getShapes() const
    {
        return *renderShapes;
    }

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

signals:
    void initializeTreeWidget();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    const alpha::vector<Shape*>* renderShapes;      // Holds currently renderedShapes
    int shapeSelectedIndex; // This is the vector index of the current shape selected, this is done so we prevent multiple shapes being selected at once
};
