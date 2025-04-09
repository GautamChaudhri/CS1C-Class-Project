#ifndef API_CLIENT_H
#define API_CLIENT_H

//CLEAN UP DOCUMENATION LATER!!!
/*
Documentation (using Qt 6.9.0)
https://doc.qt.io/qt-6/qobject.html 
https://doc.qt.io/qt-6/qnetworkaccessmanager.html 
https://doc.qt.io/qt-6/qnetworkreply.html 
https://doc.qt.io/qt-6/qnetworkrequest.html 
https://doc.qt.io/qt-6/qurl.html 
https://doc.qt.io/qt-6/qbytearray.html 
https://doc.qt.io/qt-6/qstring.html 
*/
#include <QObject>                      //Base class for all Qt Objects 
#include <QNetworkAccessManager>        //Class for sending requests and receiving replies from API Endpoints aysnchronously
#include <QNetworkReply>                //Used to read data returned from network operations
#include <QNetworkRequest>
#include <QUrl>
#include <QByteArray>
#include <QString>

class ApiClient : public QObject {
    Q_OBJECT

public:
    explicit ApiClient(QObject* parent = nullptr);
    void FetchAllShapes();

signals:
    void ShapesJsonReceived(const QString& json);
    void ErrorOccurred(const QString& error);
    /* In Qt, signals are functions that are triggered after some sort of event, in this case, when making API calls
    * When an API call is made, one of this functions will be "emitted" to signal whether the API call went through successfully
    *      or if some sort of error occurred and it failed
    * These signal functions don't need implementations, they just need to be declared
    */

private slots:
    void OnFetchAllShapesFinished();

private:
    QNetworkAccessManager* manager;  ///< Manages all network operations for the client

};

#endif //API_CLIENT_H