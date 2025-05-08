#ifndef RENDER_AREA_MANAGER
#define RENDER_AREA_MANAGER

#include <QObject>
#include <QString>
#include <QDebug>
#include <QBrush>
#include <QPen>
#include <QString>
#include "../src/backend/Parser.h"
#include "../src/objects/all_shapes.h" // ShapeId enum located here
#include "../src/objects/vector.h"

/**
 * @brief This class is a refactor of src/backend/RenderAreaManager
 *        It has been repurposed to function in this separate driver
 *        for whitebox testing. While new functions have been added
 *        and some existing ones modified, the core logic for shape 
 *        manipulation remains exactly the same as the original class.
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
    void loadHardcodedShapes() {renderedShapes = parse.JsonToShapes(GetHardcodedShapes());}
    std::string getShapesJson(const alpha::vector<Shape*>& shapes) {return parse.ShapesToJson(shapes);}
    std::string GetHardcodedShapes() {
      return R"([
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
      "ShapeId": 2,
      "TrackerId": 2471,
      "ShapeType": "Polyline",
      "ShapeDimensions": [50, 60, 80, 20, 100, 100],
      "PenColor": "green",
      "PenWidth": 4,
      "PenStyle": "SolidLine",
      "PenCapStyle": "FlatCap",
      "PenJoinStyle": "MiterJoin"
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
      }
    ])";
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

private:
    /**
     * @name Internal Data and Utilities
     * @brief Private members for storing shape data and utility objects.
     * @details This section includes the storage for shapes and instances of helper classes
     *          like ApiClient and Parser.
     */
    /** @{ */
    alpha::vector<Shape*> renderedShapes;                   ///< Vector storing pointers to all shapes currently managed.
    Parser parse;                                           ///< Parser for converting shapes to/from JSON.
    /** @} */
};
#endif