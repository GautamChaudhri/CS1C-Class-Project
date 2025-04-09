#include "ApiClient.h"


ApiClient::ApiClient(QObject* parent) : QObject{parent}, manager{new QNetworkAccessManager(this)} {}
/* The explicit keyword prevents the QObject parameter from being implicitly converted to an ApiClient object
 * The manager data member is initialized with a new instance of a QNetworkAccessManager object
 *      "this" is passed to make manager a child of the current ApiClient instance
 *      this way, the manager member is properly deleted when the ApiClient object is deleted as well, preventing memory leaks
*/

//Send a request to the Get /shapes endpoint to get all data from the shapes.json file
void ApiClient::FetchAllShapes() {
    QNetworkRequest request(QUrl("http://localhost:8080/shapes"));
    auto* reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::OnFetchAllShapesFinished);
}
/* request is an object that contains all the necessary information to make an API request
 * a request is then sent via the get() method in manager, which then returns a pointer to a QNetworkReply object that
 *      contains all of the information received from the API call
 * connect(): this line does the following
 *      the reply object represents the result of a network request and holds all of the information passed from the API
 *      When the network request is completed, the finished signal is emitted without regards to if the API request was 
 *          successful or failed due to an error. Basically, it is done getting data and is ready to be processed
 *      this is passed to to ensure that manager is owned by the current ApiCLient instance
 *      the OnFetchAllShapesFinished function is called to then act as a middle man to process the reply
 *          and figure out if it has the data we want or if an error occurred and what to do next
*/

void ApiClient::OnFetchAllShapesFinished() {
    auto* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply)
        return;
    
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        QString json = QString::fromUtf8(bytes);
        emit ShapesJsonReceived(json);
    }
    else
        emit ErrorOccurred(reply->errorString());
    
    reply->deleteLater();
}
/* Slots are functions that are connected to signals. 
 *      When a signal is emitted, its corresponding slot function is called
 * reply stores the object that emitted the signal
 *      sender() is a qt function that returns a pointer to the object that emitted the signal
 *      the pointer is then cast into a QNetworkReply object to process it
 * if the reply is not a valid QNetworkReply object:
 *      then exit the function
 * if the reply was not an error: 
 *      the data from the reply is stored in an array as bytes
 *      the bytes are then converted into a utf-8 string formatted as json
 *      the signal with the json data is emitted and sent to other parts of the program to processs it
 * if the reply was an error:
 *      the error message is emitted
 * reply->deleteLater(): the reply object is set to be deleted as soon as the application stops needing it
*/

