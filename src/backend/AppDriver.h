#ifndef APP_DRIVER_H
#define APP_DRIVER_H
#include <QCoreApplication>
#include <QObject>
#include "ShapesManager.h"
#include "RenderAreaManager.h"
#include "UserManager.h"
#include "../frontend/mainwindow.h"
#include "../frontend/renderarea.h"

class AppDriver : public QObject {
    Q_OBJECT
public:
    AppDriver(QObject* parent = nullptr);
    ~AppDriver();

    void run();
    void shutdown();


protected:
    void connectSlotsSignals();


private:
    ShapesManager* shapes;
    RenderAreaManager* renderedShapes;
    UserManager* user;
    QCoreApplication* qtApp;
};

#endif // APP_DRIVER_H