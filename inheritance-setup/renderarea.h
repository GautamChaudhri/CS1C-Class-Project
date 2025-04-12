#pragma once

#include <QWidget>
#include <QPainter>
#include <QPen>


class RenderArea : public QWidget
{
public:
    RenderArea(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);
};
