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
    const alpha::vector<Shape*>& getShapes() const;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void setShapeSelectedIndex(int newIndex);
    void resetSelection();
    void setEditPrivileges(bool edit);

    void updateShapeDisplayCoords(Shape* item, const QPoint& position) const;
    int  getShapeSelected() const;
    int  getShapeSelectedIndex() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    const alpha::vector<Shape*>* renderShapes;      // Holds currently renderedShapes
    int shapeSelectedIndex; // This is the vector index of the current shape selected, this is done so we prevent multiple shapes being selected at once
    bool allowEditing = false; // by default you cannot edit shapes
};
