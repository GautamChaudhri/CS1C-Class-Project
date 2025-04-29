#ifndef RENDER_AREA_MANAGER
#define RENDER_AREA_MANAGER
#include <QObject>
#include "ApiClient.h"
#include "Parser.h"
#include <QString>
#include "../objects/all_shapes.h"
#include "../objects/vector.h"

class RenderAreaManager : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Default Constructor
     * 
     * @details This constructor initializes the RenderAreaManager object and connects
     *          to the ApiClient signals for handling shape data.
     * 
     * @param parent - any QObject to tie this instantiation to ensure automatic deletion
     */
    explicit RenderAreaManager(QObject* parent = nullptr);
    ~RenderAreaManager();

    /**
     * @brief Returns the renderShapes vector as a reference
     */
    alpha::vector<Shape*>* getShapesRef();

    /**
     * @brief These functions are used to add, change, delete, and load shapes
     *        in the RenderAreaManager.
     * 
     * @details All of these functions emit the renderAreaChanged() signal
     *          to notify the frontend that the shapes have changed and need to be
     *          redrawn except for saveShapes
     */
    void addShape(Shape* shape);
    void modifyShape(Shape* shape, QString key, int value);
    void deleteShape(const int trackerId);
    void deleteAllShapes();
    void loadShapes();
    void saveShapes();


signals:
    /**
     * @details These signals are meant to connect to the RenderArea Window in the frontend. 
     *          -renderAreaChanged(): signal for when the renderShapes vector is changed in anyway
     *              so that the frontend knows to refresh the window and redraw the shapes
     *          -statusMessage(): signal for slot functions below. It passes the message
     *              to the frontend so it can display a popup saying the shapes were saved successfully,
     *              or whatever the message is for the user.
     */
    void renderAreaChanged();
    void renderAreaNotChanged(const QString &message);
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
    alpha::vector<Shape*> renderedShapes;
    ApiClient client;
    Parser parse;
};

#endif // RENDER_AREA_MANAGER