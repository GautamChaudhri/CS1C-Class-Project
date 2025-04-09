#include <iostream>
#include <QCoreApplication>
#include <QObject>
#include "ApiClient.h"
//#include "ApiHandler.h"   | i'm dumb and made this when we don't need it

void OnGoodResponse(const QString &json);
void OnBadResponse(const QString &errorMsg);
ApiClient* GetClient();

//Global accesss for app object;
QCoreApplication* pApp = nullptr;

//Just for testing right now. First make and run the webservice binary in the webservice folder
//and then make and run this. The output is sent to the console. You should see a string formatted as json
//directly reflecting the data in database/shapes.json. Meaning if you delete one shape in that file then run
//this again, that shape will be missing in the output and vice versa if you add a shape.
int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    pApp = &app;

    // Instantiate the ApiClient object
    ApiClient* client = GetClient();

    // Initiate the GET /shapes request; this method sends the request asynchronously.
    client->FetchAllShapes();

    // Start the Qt event loop; this loop will run until app.quit() is called.
    return app.exec();
}
/* The app variable manages the event loop and keeps main in a loop until app.quit() is called to break it
 * The client object is defined by us and is set up to make and receive api calls
 * The two connect() functions serve to connect the ApiClient signals to the lambda slot functions. They
 * are not used immediately, instead, they are just defined for now and called later when the API call completes
 * client.FetchAllShapes() is what actually makes the API call to the Get /shapes endpoint. If successful, execution
 *      jumps to the first lambda function. If it fails, it jumps to the second function
 * lambda functions are anonymous functions without a name that can be defined inline without needing to build
 *      a separate function with its own function prototypes and everything else 
*/



void OnGoodResponse(const QString &json) {
    std::cout << "Received JSON: " << json.toStdString() << std::endl;
    pApp->quit();
}

void OnBadResponse(const QString &errorMsg) {
    std::cerr << "Error: " << errorMsg.toStdString() << std::endl;
    pApp->quit();
}

ApiClient* GetClient() {
    ApiClient* client = new ApiClient(pApp);
    QObject::connect(client, &ApiClient::ShapesJsonReceived, OnGoodResponse);
    QObject::connect(client, &ApiClient::ErrorOccurred, OnBadResponse);
    return client;
}