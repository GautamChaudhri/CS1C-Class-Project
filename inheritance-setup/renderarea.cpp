#include "renderarea.h"
#include "polyline.h"
#include "polygon.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {}

void RenderArea::paintEvent(QPaintEvent *event)
{
    // TEST
    QPoint coords(5, 6);
    QBrush brush;
    brush.setColor(Qt::blue);
    QPen pen(brush, 10, Qt::DashDotLine, Qt::SquareCap, Qt::RoundJoin);
    QPolygon pointsList;
    QPolygon pointsList2;

    QPoint point(400, 500);
    QPoint point2(500, 600);
    QPoint point3(600, 750);

    QPoint point4(800, 900);
    QPoint point5(700, 850);
    QPoint point6(400, 400);
    pointsList2.push_back(point4);
    pointsList2.push_back(point5);
    pointsList2.push_back(point6);

    pointsList.push_back(point);
    pointsList.push_back(point2);
    pointsList.push_back(point3);
    Polyline polyline(1, "polyline", coords, pen, brush, pointsList);

    polyline.setBrush(Qt::blue, Qt::SolidPattern);
    polyline.setPen(Qt::blue, 3, Qt::DashDotLine, Qt::SquareCap, Qt::RoundJoin);

    Polygon polygon(2, "polygon", coords, pen, brush, pointsList2);

    polygon.setBrush(Qt::blue, Qt::SolidPattern);
    polygon.setPen(Qt::blue, 3, Qt::DashDotLine, Qt::SquareCap, Qt::RoundJoin);

    polyline.Draw(this);
    polygon.Draw(this);
    // TEST
}

