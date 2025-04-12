#include "renderarea.h"
#include "polyline.h"
#include "polygon.h"

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
    pointsList2.push_back(point4);

    pointsList.push_back(point);
    pointsList.push_back(point2);
    pointsList.push_back(point3);
    Polyline polyline(1, "polyline", coords, pen, brush, pointsList);

    polyline.setBrush(Qt::blue, Qt::SolidPattern);
    polyline.setPen(Qt::blue, 3, Qt::DashDotLine, Qt::SquareCap, Qt::RoundJoin);

    Polygon polygon(2, "polygon", coords, pen, brush, pointsList);

    polygon.setBrush(Qt::blue, Qt::SolidPattern);
    polygon.setPen(Qt::blue, 3, Qt::DashDotLine, Qt::SquareCap, Qt::RoundJoin);

    //painter.setPen(polyline.getPen());
    //painter.drawPolyline(polyline.getPointsList());

    polyline.Draw(this);
    polygon.Draw(this);
    // TEST
}

