/**
 * @file ShapesManager.h 
 * 
 * @note This class is deprecated and no longer used.
 */

#ifndef SHAPES_MANAGER
#define SHAPES_MANAGER

#include <QObject>
#include <QString>
#include <QDebug>
#include "ApiClient.h"
#include "Parser.h"
#include "../objects/all_shapes.h"
#include "../objects/vector.h"

class ShapesManager : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Default Constructor
     * 
     * @details This constructor initializes the ShapesManager object and connects
     *          to the ApiClient signals for handling shape data.
     * 
     * @param parent - any QObject to tie this instantiation to ensure automatic deletion
     */
    explicit ShapesManager(QObject* parent = nullptr);
    ~ShapesManager();

    /**
     * @brief Returns the shapes vector as a reference
     */
    alpha::vector<Shape*>* getShapesRef();

    /**
     * @brief These functions are used to add, delete, and load shapes
     *        in the ShapesManager.
     * 
     * @details All of these functions emit the shapesChanged() signal
     *          to notify the frontend that the shapes have changed and need to be
     *          redrawn except for saveShapes().
     */
    void addShape(Shape* shape);
    void modifyShape(Shape* shape);
    void deleteShape(const int trackerId);
    void deleteAllShapes();
    void loadShapes();
    void saveShapes();
    


signals:
    /**
     * @details These signals are meant to connect to the Shapes window in the frontend. 
     *          -shapesChanged(): signal for when the shapes vector is changed in any way
     *              so that the frontend knows to refresh the window and redraw the shapes
     *          -statusMessage(): signal for slot functions below. It passes the message
     *              to the frontend so it can display a popup saying the shapes were saved successfully,
     *              or whatever the message is for the user.
     */
    void shapesChanged();
    void shapesNotChanged(const QString &messsage);
    void statusMessage(const QString &message);


private slots: 
    /**
     * @details These slot functions receive signals from the ApiClient class
     * and hold the code on what to do next after one of these responses from the
     * webservice.
     */
    void onGoodGetResponse(const QString &json);
    void onBadGetResponse(const QString &errorMsg);
    void onGoodPostResponse();
    void onBadPostResponse(const QString &errorMsg);
    void onGoodDeleteResponse();
    void onBadDeleteResponse(const QString &errorMsg);


private:
    alpha::vector<Shape*> shapes;
    ApiClient client;
    Parser parse;
};

#endif // SHAPES_MANAGER
