#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setPen(Qt::blue);
    painter.setBrush(Qt::BDiagPattern);
    painter.setBrush(Qt::magenta);

    painter.drawRect(600, 400, 100, 150);

    painter.setPen(Qt::red);
    painter.setBrush(Qt::blue);
    painter.drawEllipse(150, 700, 100, 50);

    painter.setPen(Qt::green);
    painter.setPen(QPen(Qt::yellow, 3));
    painter.drawLine(800, 400, 900, 10);
}
