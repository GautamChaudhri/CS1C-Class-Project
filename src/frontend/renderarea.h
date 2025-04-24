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

    void setShapes2(const alpha::vector<Shape*>& shapes);
    void setShapes(const alpha::vector<Shape*>* shapes);
    void setRenderShapes(const alpha::vector<Shape*>* renderShapes);
    void addShape(Shape* shape)
    {
        renderShapes2.push_back(shape);
    }

    const alpha::vector<Shape*>& getShapes() const
    {
        return renderShapes2;
    }

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;


protected:
    void paintEvent(QPaintEvent *event) override;

private:
    alpha::vector<Shape*> renderShapes2;
    const alpha::vector<Shape*>* allShapes;         // Holds all possible shapes that can be rendered
    const alpha::vector<Shape*>* renderShapes;      // Holds currently renderedShapes
    int shapeSelectedIndex; // This is the vector index of the current shape selected, this is done so we prevent multiple shapes being selected at once
};
