#include <QWidget>
#include <QPainter>
#include <QPen>

class RenderArea : public QWidget
{
public:
    RenderArea(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    void paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);

        // prevents shapes from drawing out of bounds
        painter.setClipRect(50,105,1000,850);

        painter.setPen(Qt::blue);
        painter.setBrush(Qt::BDiagPattern);
        painter.setBrush(Qt::red);

        painter.drawRect(600, 400, 100, 70);

        painter.setPen(Qt::red);
        painter.setBrush(Qt::blue);
        painter.drawEllipse(150, 700, 100, 50);

        painter.setPen(Qt::green);
        painter.setPen(QPen(Qt::blue, 3));
        painter.drawLine(800, 400, 900, 10);
    }
};
