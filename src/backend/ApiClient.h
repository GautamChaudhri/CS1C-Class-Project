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

/**
 * @brief Manages network communication with the backend API.
 *
 * This class provides methods to perform GET, POST, and DELETE requests
 * to various endpoints of the webservice. It uses QNetworkAccessManager
 * for handling network operations and emits signals to indicate the success
 * or failure of these requests.
 */
class ApiClient : public QObject {
    Q_OBJECT    //necessary macro for qt's compiler

public:
    /**
     * @name Constructor and Core API Functions
     * @brief Public methods for ApiClient.
     * @details This section includes the constructor and functions for making API requests.
     */
    /** @{ */
    explicit ApiClient(QObject* parent = nullptr);                  ///< Default Constructor.
    /** @} */


    /**
     * @name Shape Data Management
     * @brief API endpoints for managing Shape data.
     * @details These functions interact with the `/shapes` and `/shapes-all` endpoints
     *          to retrieve, submit, or delete shape information.
     * 
     * @note These endpoints are deprecated 
     */
    /** @{ */
    void GetShapes();                                               ///< Makes a request to get data from the Get /shapes API Endpoint.
    void PostShapes(std::string json);                              ///< Makes a request to send data to the Post /shapes API Endpoint.
    void DeleteShapesAll();                                         ///< Makes a request to delete all shapes via the Delete /shapes-all endpoint.
    /** @} */


    /**
     * @name Render Area Data Management
     * @brief API endpoints for managing Render Area data.
     * @details These functions interact with the `/render_area` and `/render_area-all` endpoints
     *          to retrieve, submit, or delete render area configurations.
     */
    /** @{ */
    void GetRenderArea();                                           ///< Makes a request to get data from the Get /render_area API Endpoint.
    void PostRenderArea(std::string json);                          ///< Makes a request to send data to the Post /render_area API Endpoint.
    void DeleteRenderAreaAll();                                     ///< Makes a request to delete all render area data via Delete /render_area-all.
    /** @} */


    /**
     * @name User Data Management
     * @brief API endpoints for managing User data.
     * @details These functions interact with the `/users` and `/users-all` endpoints
     *          to retrieve, submit, or delete user information.
     */
    /** @{ */
    void GetUsers();                                                ///< Makes a request to get data from the Get /users API Endpoint.
    void PostUsers(std::string json);                               ///< Makes a request to send data to the Post /users API Endpoint.
    void DeleteUsersAll();                                          ///< Makes a request to delete all user data via Delete /users-all.
    /** @} */


    /**
     * @name Testimonial Data Management
     * @brief API endpoints for managing Testimonial data.
     * @details These functions interact with the `/testimonials` endpoint
     *          to retrieve, submit, or delete testimonial entries.
     */
    /** @{ */
    void GetTestimonials();                                         ///< Makes a request to get all testimonials via GET /testimonials.
    void PostTestimonials(std::string json);                        ///< Makes a request to post testimonial data via POST /testimonials.
    void DeleteTestimonialsAll();                                   ///< Makes a request to delete all testimonials via DELETE /testimonials.
    /** @} */


signals:
    /**
     * @name API Reply Signals
     * @brief Signals emitted by ApiClient to communicate request outcomes.
     * @details These signals notify listeners about the success or failure of
     *          GET, POST, and DELETE operations.
     */
    /** @{ */
    void GoodGetReply(const QString& json);                         ///< Signal for a successful request sent to a Get endpoint.
    void BadGetReply(const QString& error);                         ///< Signal for a failed request sent to a Get endpoint.
    void GoodPostReply();                                           ///< Signal for a successful request sent to a Post endpoint.
    void BadPostReply(const QString& error);                        ///< Signal for a failed request sent to a Post endpoint.
    void GoodDeleteReply();                                         ///< Signal for a successful request sent to a Delete endpoint.
    void BadDeleteReply(const QString& error);                      ///< Signal for a failed request sent to a Delete endpoint.
    /** @} */


private slots:
    /**
     * @name Network Reply Analysis
     * @brief These slots are connected to the finished signal of QNetworkReply
     * and determine whether the operation was successful, emitting the
     * appropriate Good/Bad Get/Post/Delete reply signals.
     */
    /** @{ */
    void AnalyzeGetReply();                                         ///< Analyzes the reply for GET requests.
    void AnalyzePostReply();                                        ///< Analyzes the reply for POST requests.
    void AnalyzeDeleteReply();                                      ///< Analyzes the reply for DELETE requests.
    /** @} */

    
private:
    QNetworkAccessManager* manager;                                 ///< Manages all network operations for the client.
};

#endif //API_CLIENT_H