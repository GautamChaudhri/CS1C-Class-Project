/**
 * @file ApiClient.h
 * @brief Implements the ApiClient class that makes API requests to the Crow Webservice
 *
 * @details This class interacts with the following endpoints through the corresponding member functions
 *          Get /shapes         : GetShapes()
 *          Post /shapes        : PostShapes()
 *          Get /render_area    : GetRenderArea()
 *          Post /render_area   : PostRenderArea()
 */
#ifndef API_CLIENT_H
#define API_CLIENT_H
                                    ///Documentation Qt Version 6.9.0
#include <QObject>                  // https://doc.qt.io/qt-6/qobject.html 
#include <QNetworkAccessManager>    // https://doc.qt.io/qt-6/qnetworkaccessmanager.html 
#include <QNetworkReply>            // https://doc.qt.io/qt-6/qnetworkreply.html      
#include <QNetworkRequest>          // https://doc.qt.io/qt-6/qnetworkrequest.html 
#include <QUrl>                     // https://doc.qt.io/qt-6/qurl.html  
#include <QByteArray>               // https://doc.qt.io/qt-6/qbytearray.html 
#include <QString>                  // https://doc.qt.io/qt-6/qstring.html 

class ApiClient : public QObject {
    Q_OBJECT    //necessary macro for qt's compiler

public:
    /**
     * @brief Default Constructor
     * 
     * @param parent - any QObject to tie this instantiation to ensure automatic deletion
     */
    explicit ApiClient(QObject* parent = nullptr);

    /**
     * @brief Makes a request to get data from the Get /shapes API Endpoint
     * @file reads from database/shapes.json
     * 
     * @details This function submits a request to the Get /shapes API in the webservice. 
     *          On completion of request, control is handed over to @see AnalyzeGetReply().
     */
    void GetShapes();

    /**
     * @brief Makes a request to get data from the Get /render_area API Endpoint
     * @file reads from database/render_area.json
     * 
     * @details This function submits a request to the Get /render_area API in the webservice. 
     *          On completion of request, control is handed over to @see AnalyzeGetReply().
     */
    void GetRenderArea();

    /**
     * @brief Makes a request to send data to the Post /shapes API Endpoint
     * @file writes to database/shapes.json
     * 
     * @details This function submits a request to the Post /shapes API in the webservice. 
     *          On completion of request, control is handed over to @see AnalyzePostReply(). 
     * 
     * @param json - contains data for all possible shapes that can be rendered by the 
     *               application; formatted in JSON
     */
    void PostShapes(std::string json);

    /**
     * @brief Makes a request to get data from the Post /render_area API Endpoint
     * @file writes to database/render_area.json
     * 
     * @details This function submits a request to the Post /render_area API in the webservice. 
     *          On completion of request, control is handed over to @see AnalyzePostReply().
     * 
     * @param json - contains data for all shapes currently in the render window in the 
     *               frontend UI; formatted in JSON
     */
    void PostRenderArea(std::string json);

signals:
    /**
     * @brief Signal for a successful request sent to a Get endpoint
     * 
     * @details When this signal is emitted, the ApiClient object contains the data that we want 
     *          formatted in JSON.
     * 
     * @param json - contains data received from whichever Get endpoint was called and is formatted in JSON.
     */
    void GoodGetReply(const QString& json);

    /**
     * @brief Signal for a failed request sent to a Get endpoint
     * 
     * @details When this signal is emitted, the ApiClient object does not have the data we want. Instead, 
     *          it contains an error message on what went wrong.
     * 
     * @param error - the error message indicating what went wrong
     */
    void BadGetReply(const QString& error);

    /**
     * @brief Signal for a successful request sent to a Post endpoint
     * 
     * @details When this signal is emitted, then the data was successfully received by the API.
     */
    void GoodPostReply();

    /**
     * @brief Signal for a failed request sent to a Post endpoint
     * 
     * @details When this signal is emitted, then the API was not able to properly update the file it needed to. 
     *          Assume the data sent was not saved.
     * 
     * @param error - the error message indicating what went wrong
     */
    void BadPostReply(const QString& error);

private slots:
    /**
     * @brief Analyzes the reply to discover if the Get request sent was successful or a failure.
     * 
     * @details A successful reply emits the @see GoodGetReply signal. An errored reply emits the 
     *          @see BadGetReply signal. After signal emission, what happens next is implemented
     *          in @see main.cpp.
     */
    void AnalyzeGetReply();

    /**
     * @brief Analyzes the reply to discover if the Post request sent was successful or a failure.
     * 
     * @details A successful reply emits the @see GoodPostReply signal. An errored reply emits the 
     *          @see BadPostReply signal. After signal emission, what happens next is implemented
     *          in @see main.cpp.
     */
    void AnalyzePostReply();

private:
    QNetworkAccessManager* manager;  // Manages all network operations for the client
};

#endif //API_CLIENT_H