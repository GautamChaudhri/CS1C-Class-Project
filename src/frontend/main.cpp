#include "../backend/AppDriver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AppDriver driver;

    driver.run();
    return a.exec();
}
