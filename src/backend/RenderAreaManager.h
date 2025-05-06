#ifndef RENDER_AREA_MANAGER
#define RENDER_AREA_MANAGER

#include <QObject>
#include <QString>
#include <QDebug>
#include <QBrush>
#include <QPen>
#include "ApiClient.h"
#include "Parser.h"
#include <QString>
#include "../objects/all_shapes.h" // ShapeId enum located here
#include "../objects/vector.h"

/**
 * @brief Manages the shapes to be rendered and interacts with the backend API.
 *
 * This class is responsible for adding, modifying, deleting, loading, and saving shapes.
 * It communicates with an ApiClient to persist shape data and uses a Parser
 * for serialization and deserialization. It also emits signals when the render area
 * needs to be updated or when status messages should be displayed.
 */
class RenderAreaManager : public QObject {
    Q_OBJECT

public:
    /**
     * @name Core Management Functions
     * @brief Public methods for RenderAreaManager.
     * @details This section includes constructors, destructors, and primary interface
     *          functions for managing and accessing shape data.
     */
    /** @{ */
    explicit RenderAreaManager(QObject* parent = nullptr);  ///< Constructs a RenderAreaManager object and connects API client signals.
    ~RenderAreaManager();                                   ///< Destroys the RenderAreaManager object and deallocates rendered shapes.

    alpha::vector<Shape*>* getShapesRef();                  ///< Retrieves a pointer to the vector of rendered shapes.
    /** @} */

    /**
     * @name Shape Manipulation
     * @brief Functions for manipulating shapes within the RenderAreaManager.
     * @details These methods handle the creation, modification, and deletion of shapes.
     *          Most of these operations will trigger a signal to update the rendering area
     *          and will attempt to save the changes to the backend.
     */
    /** @{ */
    void addShape(Shape* shape);                            ///< Adds a new shape to the rendering list and triggers a save.
    void modifyShape(Shape* shape, QString key, int value); ///< Modifies a property of an existing shape based on a key-value pair.
    void modifyDisplayedText(Text* obj, QString newText);   ///< Modifies the displayed text of a Text shape.
    void deleteShape(const int trackerId);                  ///< Deletes a shape identified by its tracker ID.
    void deleteAllShapes();                                 ///< Requests the deletion of all shapes from the backend.
    void loadShapes();                                      ///< Initiates loading shapes from the backend webservice.
    void saveShapes();                                      ///< Initiates saving the current shapes to the backend webservice.
    /** @} */


signals:
    /**
     * @name Render Area Signals
     * @brief Signals emitted by RenderAreaManager to communicate with other parts of the application.
     * @details These signals are primarily used to notify the UI about changes in the
     *          shape data or to convey status messages.
     */
    /** @{ */
    void renderAreaChanged();                               ///< Emitted when the render area has changed and needs redrawing.
    void renderAreaNotChanged(const QString &message);      ///< Emitted when an operation completes without changing the render area, often with a message.
    void statusMessage(const QString &message);             ///< Emitted to provide a status message to the user.
    /** @} */


private slots:
    /**
     * @name API Client Response Handlers
     * @brief Private slots for handling responses from the ApiClient.
     * @details These slots are connected to signals from the ApiClient and process
     *          the results of asynchronous network operations (GET, POST, DELETE).
     */
    /** @{ */
    void onGoodGetResponse(const QString &json);            ///< Slot to handle successful GET responses from the API client.
    void onBadGetResponse(const QString &errorMsg);         ///< Slot to handle unsuccessful GET responses from the API client.
    void onGoodPostResponse();                              ///< Slot to handle successful POST responses from the API client.
    void onBadPostResponse(const QString &errorMsg);        ///< Slot to handle unsuccessful POST responses from the API client.
    void onGoodDeleteResponse();                            ///< Slot to handle successful DELETE responses from the API client.
    void onBadDeleteResponse(const QString &errorMsg);      ///< Slot to handle unsuccessful DELETE responses from the API client.
    /** @} */


private:
    /**
     * @name Internal Data and Utilities
     * @brief Private members for storing shape data and utility objects.
     * @details This section includes the storage for shapes and instances of helper classes
     *          like ApiClient and Parser.
     */
    /** @{ */
    alpha::vector<Shape*> renderedShapes;                   ///< Vector storing pointers to all shapes currently managed.
    ApiClient client;                                       ///< Client for making API requests to the backend.
    Parser parse;                                           ///< Parser for converting shapes to/from JSON.
    /** @} */
};

#endif // RENDER_AREA_MANAGER
