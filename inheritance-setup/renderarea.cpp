#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent) {}

void RenderArea::paintEvent(QPaintEvent *event)
{
    // TEST
    QPoint coords(500, 500);
    QBrush brush(Qt::blue);
    QPen pen(Qt::blue);

    std::unique_ptr<Shape> shape = std::make_unique<Square>(1, "Square", coords, pen, brush, 50);
    addShape(std::move(shape));

    int vecSize;
    vecSize = renderShapes.size();

    for(int i = 0; i < vecSize; ++i)
    {
        renderShapes[i]->Draw(this);
    }

    // QPolygon pointsList;
    // QPolygon pointsList2;

    // QPoint point(400, 500);
    // QPoint point2(500, 600);
    // QPoint point3(600, 750);

    // QPoint point4(800, 900);
    // pointsList2.push_back(point4);

    // pointsList.push_back(point);
    // pointsList.push_back(point2);
    // pointsList.push_back(point3);

    //Polyline polyline(1, "polyline", coords, pen, brush, pointsList);
    //Polygon polygon(2, "polygon", coords, pen, brush, pointsList);

    // polygon.setBrush(Qt::blue, Qt::SolidPattern);
    // polygon.setPen(Qt::blue, 3, Qt::DashDotLine, Qt::SquareCap, Qt::RoundJoin);

    //painter.setPen(polyline.getPen());
    //painter.drawPolyline(polyline.getPointsList());

    //polyline.Draw(this);
    //polygon.Draw(this);

    // polygon.setBrush(Qt::blue, Qt::SolidPattern);
    // polygon.setPen(Qt::blue, 3, Qt::DashDotLine, Qt::SquareCap, Qt::RoundJoin);
}

