#include "../backend/AppDriver.h"


int main(int argc, char *argv[]) {
    
    // turn on per-monitor high-DPI scaling
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication app(argc, argv);
    AppDriver driver;

    driver.run();
    return app.exec();
}
