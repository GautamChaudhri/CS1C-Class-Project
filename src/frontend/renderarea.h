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

    void setShapes(const alpha::vector<Shape*>& shapes);
    void setShapes(const alpha::vector<Shape*>* shapes);
    void addShape(Shape* shape)
    {
        renderShapes.push_back(shape);
    }

    const alpha::vector<Shape*>& getShapes() const
    {
        return renderShapes;
    }

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

public slots:
    void onRenderAreaChanged(const alpha::vector<Shape*>* shapes);
    void onRenderAreaNotChanged(const QString& message);
    void showStatusMessage(QString msg);

signals:
    void shapeAdded(Shape* shape);
    void shapeChanged(Shape* shape);
    void shapeDeleted(int trackerId);
    void deleteAllShapes();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    alpha::vector<Shape*> renderShapes;
    const alpha::vector<Shape*> renderShapes2;
    int shapeSelectedIndex; // This is the vector index of the current shape selected, this is done so we prevent multiple shapes being selected at once
};
