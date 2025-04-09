#include <iostream>
#include <QCoreApplication>
#include <QObject>
#include <QTimer>
#include "ApiClient.h"

// Define a controller class to handle ApiClient signals without lambdas.
class MyAppController : public QObject {
    Q_OBJECT
public:
    explicit MyAppController(QCoreApplication* app, QObject* parent = nullptr)
        : QObject(parent), m_app(app)
    {
        // Connect signals to the corresponding member slots.
        connect(&client, &ApiClient::ShapesJsonReceived, this, &MyAppController::onShapesJsonReceived);
        connect(&client, &ApiClient::ErrorOccurred, this, &MyAppController::onErrorOccurred);
        // Initiate the API call after the event loop starts.
        QTimer::singleShot(0, &client, &ApiClient::FetchAllShapes);
    }

public slots:
    void onShapesJsonReceived(const QString &json) {
        std::cout << "Received JSON: " << json.toStdString() << std::endl;
        m_app->quit();
    }
    void onErrorOccurred(const QString &error) {
        std::cerr << "Error: " << error.toStdString() << std::endl;
        m_app->quit();
    }

private:
    QCoreApplication* m_app;
    ApiClient client;
};

#include "main.moc"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    MyAppController controller(&app);
    return app.exec();
}