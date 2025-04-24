#include "mainwindow.h"
#include "shapecontroller.h"
#include <QFile>
#include "../backend/AppDriver.h"

Parser parse;
ShapeController shapeController;
MainWindow* windowPtr = nullptr;

void OnGoodGetResponseTest(const QString &json) {
    std::string jsonStr = json.toStdString();
    alpha::vector<Shape*> parsed = parse.JsonToShapes(jsonStr);
    emit shapeController.ShapesReady(parsed);
}

void OnBadGetResponseTest(const QString &errorMsg) {
    // Handle error
}

void OnGoodPostResponseTest() {}
void OnBadPostResponseTest(const QString &errorMsg) {}

ApiClient* GetConnectedClient() {
    ApiClient* client = new ApiClient();
    QObject::connect(client, &ApiClient::GoodGetReply, OnGoodGetResponseTest);
    QObject::connect(client, &ApiClient::BadGetReply, OnBadGetResponseTest);
    QObject::connect(client, &ApiClient::GoodPostReply, OnGoodPostResponseTest);
    QObject::connect(client, &ApiClient::BadPostReply, OnBadPostResponseTest);
    return client;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AppDriver driver;

    driver.run();
    // MainWindow window;
    // windowPtr = &window;

    // QObject::connect(&shapeController, &ShapeController::ShapesReady, &window, &MainWindow::setShapes);
    // QObject::connect(&shapeController, &ShapeController::ShapesReady, [&window]() { window.shapes_to_treeWidget();});

     ApiClient* client = GetConnectedClient();
     client->GetShapes();  // triggers API call

    // window.show();
    return a.exec();
}
