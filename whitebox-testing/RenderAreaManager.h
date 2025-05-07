#ifndef RENDER_AREA_MANAGER
#define RENDER_AREA_MANAGER

#include <QObject>
#include <QString>
#include <QDebug>
#include <QBrush>
#include <QPen>
#include <QString>
#include "../src/backend/ApiClient.h"
#include "../src/backend/Parser.h"
#include "../src/objects/all_shapes.h" // ShapeId enum located here
#include "../src/objects/vector.h"

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

    //For Whitebox Testing
    alpha::vector<Shape*> getShapesVector() {return renderedShapes;} 
    void loadHardcodedShapes() {
        renderedShapes = parse.JsonToShapes(GetHardcodedShapes());
    }
    

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

    //For Whitebox testing
    std::string GetHardcodedShapes() {
        return R"([
        {
          "ShapeId": 3,
          "TrackerId": 3214,
          "ShapeType": "Polygon",
          "ShapeDimensions": [100, 100, 150, 50, 200, 100],
          "PenColor": "yellow",
          "PenWidth": 2,
          "PenStyle": "SolidLine",
          "PenCapStyle": "FlatCap",
          "PenJoinStyle": "MiterJoin",
          "BrushColor": "darkGray",
          "BrushStyle": "Dense1Pattern"
        },
        {
          "ShapeId": 4,
          "TrackerId": 4098,
          "ShapeType": "Rectangle",
          "ShapeDimensions": [10, 10, 200, 100],
          "PenColor": "gray",
          "PenWidth": 5,
          "PenStyle": "DashLine",
          "PenCapStyle": "RoundCap",
          "PenJoinStyle": "RoundJoin",
          "BrushColor": "black",
          "BrushStyle": "NoBrush"
        },
        {
          "ShapeId": 5,
          "TrackerId": 5890,
          "ShapeType": "Square",
          "ShapeDimensions": [50, 50, 50],
          "PenColor": "red",
          "PenWidth": 2,
          "PenStyle": "DotLine",
          "PenCapStyle": "FlatCap",
          "PenJoinStyle": "RoundJoin",
          "BrushColor": "blue",
          "BrushStyle": "DiagCrossPattern"
        },
        {
          "ShapeId": 6,
          "TrackerId": 6799,
          "ShapeType": "Ellipse",
          "ShapeDimensions": [600, 200, 120, 80],
          "PenColor": "green",
          "PenWidth": 3,
          "PenStyle": "DashLine",
          "PenCapStyle": "FlatCap",
          "PenJoinStyle": "BevelJoin",
          "BrushColor": "white",
          "BrushStyle": "Dense1Pattern"
        },
        {
          "ShapeId": 1,
          "TrackerId": 1534,
          "ShapeType": "Line",
          "ShapeDimensions": [0, 0, 500, 500],
          "PenColor": "blue",
          "PenWidth": 4,
          "PenStyle": "DashDotDotLine",
          "PenCapStyle": "SquareCap",
          "PenJoinStyle": "MiterJoin"
        },
        {
          "ShapeId": 2,
          "TrackerId": 2670,
          "ShapeType": "Polyline",
          "ShapeDimensions": [20, 30, 40, 50, 60, 70],
          "PenColor": "lightGray",
          "PenWidth": 2,
          "PenStyle": "SolidLine",
          "PenCapStyle": "RoundCap",
          "PenJoinStyle": "MiterJoin"
        },
        {
          "ShapeId": 7,
          "TrackerId": 7104,
          "ShapeType": "Circle",
          "ShapeDimensions": [100, 100, 60],
          "PenColor": "green",
          "PenWidth": 1,
          "PenStyle": "SolidLine",
          "PenCapStyle": "FlatCap",
          "PenJoinStyle": "BevelJoin",
          "BrushColor": "yellow",
          "BrushStyle": "HorPattern"
        },
        {
          "ShapeId": 8,
          "TrackerId": 8999,
          "ShapeType": "Text",
          "ShapeDimensions": [200, 700, 400, 30],
          "TextString": "Test Shape Text",
          "TextColor": "black",
          "TextAlignment": "AlignLeft",
          "TextPointSize": 12,
          "TextFontFamily": "Courier",
          "TextFontStyle": "StyleItalic",
          "TextFontWeight": "Normal"
        },
        {
          "ShapeId": 6,
          "TrackerId": 6044,
          "ShapeType": "Ellipse",
          "ShapeDimensions": [150, 150, 90, 45],
          "PenColor": "cyan",
          "PenWidth": 3,
          "PenStyle": "DotLine",
          "PenCapStyle": "FlatCap",
          "PenJoinStyle": "MiterJoin",
          "BrushColor": "blue",
          "BrushStyle": "Dense1Pattern"
        },
        {
          "ShapeId": 3,
          "TrackerId": 3933,
          "ShapeType": "Polygon",
          "ShapeDimensions": [700, 100, 750, 50, 800, 100],
          "PenColor": "black",
          "PenWidth": 2,
          "PenStyle": "DashDotLine",
          "PenCapStyle": "FlatCap",
          "PenJoinStyle": "MiterJoin",
          "BrushColor": "gray",
          "BrushStyle": "CrossPattern"
        },
        {
          "ShapeId": 4,
          "TrackerId": 4632,
          "ShapeType": "Rectangle",
          "ShapeDimensions": [300, 300, 100, 200],
          "PenColor": "white",
          "PenWidth": 3,
          "PenStyle": "SolidLine",
          "PenCapStyle": "RoundCap",
          "PenJoinStyle": "RoundJoin",
          "BrushColor": "blue",
          "BrushStyle": "Dense1Pattern"
        },
        {
          "ShapeId": 5,
          "TrackerId": 5012,
          "ShapeType": "Square",
          "ShapeDimensions": [100, 100, 120],
          "PenColor": "black",
          "PenWidth": 4,
          "PenStyle": "DashLine",
          "PenCapStyle": "RoundCap",
          "PenJoinStyle": "RoundJoin",
          "BrushColor": "red",
          "BrushStyle": "SolidPattern"
        }
      ])";
    }
};
#endif