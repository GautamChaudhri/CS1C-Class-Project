#include <iostream>
#include <QCoreApplication>
#include <QObject>
#include "ApiClient.h"
//#include "ApiHandler.h"   | i'm dumb and made this when we don't need it

void OnGoodGetResponseTest(const QString &json);
void OnBadGetResponseTest(const QString &errorMsg);
void OnGoodPostResponseTest();
void OnBadPostResponseTest(const QString &errorMsg);
ApiClient* GetConnectedClient();

//For testing
std::string GetShapeTestString();
std::string GetRenderAreaTestString();

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
    ApiClient* client = GetConnectedClient();

    //std::string testStr = GetShapeTestString();
    client->GetShapes();
    
    //testStr = GetRenderAreaTestString();
    client->GetRenderArea();

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

void OnGoodGetResponseTest(const QString &json) {
    std::cout << "Received JSON:\n" << json.toStdString() << std::endl << std::endl;
    //pApp->quit();
}

void OnBadGetResponseTest(const QString &errorMsg) {
    std::cerr << "Error: " << errorMsg.toStdString() << std::endl << std::endl;
    //pApp->quit();
}

void OnGoodPostResponseTest() {
    std::cout << "Data Received by webservice successfully!\n";
    //pApp->quit();
}

void OnBadPostResponseTest(const QString &errorMsg) {
    std::cerr << "Error: " << errorMsg.toStdString() << std::endl;
    //pApp->quit();
}

ApiClient* GetConnectedClient() {
    ApiClient* client = new ApiClient(pApp);
    QObject::connect(client, &ApiClient::GoodGetReply, OnGoodGetResponseTest);
    QObject::connect(client, &ApiClient::BadGetReply, OnBadGetResponseTest);
    QObject::connect(client, &ApiClient::GoodPostReply, OnGoodPostResponseTest);
    QObject::connect(client, &ApiClient::BadPostReply, OnBadPostResponseTest);
    return client;
}

//For testing
std::string GetShapeTestString() {
    return R"([
    {
      "ShapeId": 1,
      "TrackingId": null,
      "ShapeType": "Line",
      "ShapeDimensions": [20, 90, 100, 20],
      "PenColor": "blue",
      "PenWidth": 2,
      "PenStyle": "DashDotLine",
      "PenCapStyle": "FlatCap",
      "PenJoinStyle": "MiterJoin"
    },
    {
      "ShapeId": 2,
      "TrackingId": null,
      "ShapeType": "Polyline",
      "ShapeDimensions": [460, 90, 470, 20, 530, 40, 540, 80],
      "PenColor": "green",
      "PenWidth": 6,
      "PenStyle": "SolidLine",
      "PenCapStyle": "FlatCap",
      "PenJoinStyle": "MiterJoin"
    },
    {
      "ShapeId": 3,
      "TrackingId": null,
      "ShapeType": "Polygon",
      "ShapeDimensions": [900, 90, 910, 20, 970, 40, 980, 80],
      "PenColor": "cyan",
      "PenWidth": 6,
      "PenStyle": "DashDotDotLine",
      "PenCapStyle": "FlatCap",
      "PenJoinStyle": "MiterJoin",
      "BrushColor": "yellow",
      "BrushStyle": "SolidPattern"
    },
    {
      "ShapeId": 4,
      "TrackingId": null,
      "ShapeType": "Rectangle",
      "ShapeDimensions": [20, 200, 170, 100],
      "PenColor": "blue",
      "PenWidth": 0,
      "PenStyle": "DashLine",
      "PenCapStyle": "RoundCap",
      "PenJoinStyle": "RoundJoin",
      "BrushColor": "red",
      "BrushStyle": "VerPattern"
    },
    {
      "ShapeId": 5,
      "TrackingId": null,
      "ShapeType": "Square",
      "ShapeDimensions": [250, 150, 200],
      "PenColor": "red",
      "PenWidth": 0,
      "PenStyle": "SolidLine",
      "PenCapStyle": "RoundCap",
      "PenJoinStyle": "RoundJoin",
      "BrushColor": "blue",
      "BrushStyle": "HorPattern"
    },
    {
      "ShapeId": 6,
      "TrackingId": null,
      "ShapeType": "Ellipse",
      "ShapeDimensions": [520, 200, 170, 100],
      "PenColor": "black",
      "PenWidth": 12,
      "PenStyle": "SolidLine",
      "PenCapStyle": "FlatCap",
      "PenJoinStyle": "MiterJoin",
      "BrushColor": "white",
      "BrushStyle": "NoBrush"
    },
    {
      "ShapeId": 7,
      "TrackingId": null,
      "ShapeType": "Circle",
      "ShapeDimensions": [750, 150, 200],
      "PenColor": "black",
      "PenWidth": 12,
      "PenStyle": "SolidLine",
      "PenCapStyle": "FlatCap",
      "PenJoinStyle": "MiterJoin",
      "BrushColor": "magenta",
      "BrushStyle": "SolidPattern"
    },
    {
      "ShapeId": 8,
      "TrackingId": null,
      "ShapeType": "Text",
      "ShapeDimensions": [250, 425, 500, 50],
      "TextString": "Class Project 2 - 2D Graphics Modeler",
      "TextColor": "blue",
      "TextAlignment": "AlignCenter",
      "TextPointSize": 10,
      "TextFontFamily": "Comic Sans MS",
      "TextFontStyle": "StyleItalic",
      "TextFontWeight": "Normal"
    }
  ])";
}

std::string GetRenderAreaTestString() {
    return R"([
    {
      "ShapeId": 1,
      "TrackingId": 1320,
      "ShapeType": "Line",
      "ShapeDimensions": [34, 76, 123, 89],
      "PenColor": "red",
      "PenWidth": 3,
      "PenStyle": "DashLine",
      "PenCapStyle": "RoundCap",
      "PenJoinStyle": "BevelJoin"
    },
    {
      "ShapeId": 2,
      "TrackingId": 2471,
      "ShapeType": "Polyline",
      "ShapeDimensions": [50, 60, 80, 20, 100, 100],
      "PenColor": "green",
      "PenWidth": 4,
      "PenStyle": "SolidLine",
      "PenCapStyle": "FlatCap",
      "PenJoinStyle": "MiterJoin"
    },
    {
      "ShapeId": 3,
      "TrackingId": 3619,
      "ShapeType": "Polygon",
      "ShapeDimensions": [300, 300, 350, 250, 400, 300],
      "PenColor": "blue",
      "PenWidth": 5,
      "PenStyle": "DotLine",
      "PenCapStyle": "FlatCap",
      "PenJoinStyle": "MiterJoin",
      "BrushColor": "yellow",
      "BrushStyle": "SolidPattern"
    },
    {
      "ShapeId": 4,
      "TrackingId": 4383,
      "ShapeType": "Rectangle",
      "ShapeDimensions": [400, 400, 150, 100],
      "PenColor": "blue",
      "PenWidth": 2,
      "PenStyle": "DashDotLine",
      "PenCapStyle": "RoundCap",
      "PenJoinStyle": "RoundJoin",
      "BrushColor": "cyan",
      "BrushStyle": "HorPattern"
    },
    {
      "ShapeId": 5,
      "TrackingId": 5524,
      "ShapeType": "Square",
      "ShapeDimensions": [500, 500, 80],
      "PenColor": "orange",
      "PenWidth": 1,
      "PenStyle": "SolidLine",
      "PenCapStyle": "RoundCap",
      "PenJoinStyle": "RoundJoin",
      "BrushColor": "magenta",
      "BrushStyle": "VerPattern"
    },
    {
      "ShapeId": 6,
      "TrackingId": 6852,
      "ShapeType": "Ellipse",
      "ShapeDimensions": [200, 200, 100, 60],
      "PenColor": "black",
      "PenWidth": 6,
      "PenStyle": "DashDotDotLine",
      "PenCapStyle": "FlatCap",
      "PenJoinStyle": "MiterJoin",
      "BrushColor": "green",
      "BrushStyle": "SolidPattern"
    },
    {
      "ShapeId": 7,
      "TrackingId": 7901,
      "ShapeType": "Circle",
      "ShapeDimensions": [300, 300, 90],
      "PenColor": "black",
      "PenWidth": 8,
      "PenStyle": "SolidLine",
      "PenCapStyle": "FlatCap",
      "PenJoinStyle": "MiterJoin",
      "BrushColor": "red",
      "BrushStyle": "Dense1Pattern"
    },
    {
      "ShapeId": 8,
      "TrackingId": 8675,
      "ShapeType": "Text",
      "ShapeDimensions": [100, 600, 300, 40],
      "TextString": "Sample Text A",
      "TextColor": "purple",
      "TextAlignment": "AlignCenter",
      "TextPointSize": 14,
      "TextFontFamily": "Arial",
      "TextFontStyle": "StyleNormal",
      "TextFontWeight": "Bold"
    },
    {
      "ShapeId": 3,
      "TrackingId": 3214,
      "ShapeType": "Polygon",
      "ShapeDimensions": [100, 100, 150, 50, 200, 100],
      "PenColor": "teal",
      "PenWidth": 2,
      "PenStyle": "SolidLine",
      "PenCapStyle": "FlatCap",
      "PenJoinStyle": "MiterJoin",
      "BrushColor": "pink",
      "BrushStyle": "Dense4Pattern"
    },
    {
      "ShapeId": 4,
      "TrackingId": 4098,
      "ShapeType": "Rectangle",
      "ShapeDimensions": [10, 10, 200, 100],
      "PenColor": "gray",
      "PenWidth": 5,
      "PenStyle": "DashLine",
      "PenCapStyle": "RoundCap",
      "PenJoinStyle": "RoundJoin",
      "BrushColor": "orange",
      "BrushStyle": "NoBrush"
    },
    {
      "ShapeId": 5,
      "TrackingId": 5890,
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
      "TrackingId": 6799,
      "ShapeType": "Ellipse",
      "ShapeDimensions": [600, 200, 120, 80],
      "PenColor": "green",
      "PenWidth": 3,
      "PenStyle": "DashLine",
      "PenCapStyle": "FlatCap",
      "PenJoinStyle": "BevelJoin",
      "BrushColor": "white",
      "BrushStyle": "Dense7Pattern"
    },
    {
      "ShapeId": 1,
      "TrackingId": 1534,
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
      "TrackingId": 2670,
      "ShapeType": "Polyline",
      "ShapeDimensions": [20, 30, 40, 50, 60, 70],
      "PenColor": "navy",
      "PenWidth": 2,
      "PenStyle": "SolidLine",
      "PenCapStyle": "RoundCap",
      "PenJoinStyle": "MiterJoin"
    },
    {
      "ShapeId": 7,
      "TrackingId": 7104,
      "ShapeType": "Circle",
      "ShapeDimensions": [100, 100, 60],
      "PenColor": "maroon",
      "PenWidth": 1,
      "PenStyle": "SolidLine",
      "PenCapStyle": "FlatCap",
      "PenJoinStyle": "BevelJoin",
      "BrushColor": "yellow",
      "BrushStyle": "HorPattern"
    },
    {
      "ShapeId": 8,
      "TrackingId": 8999,
      "ShapeType": "Text",
      "ShapeDimensions": [200, 700, 400, 30],
      "TextString": "Test Shape Text",
      "TextColor": "black",
      "TextAlignment": "AlignLeft",
      "TextPointSize": 12,
      "TextFontFamily": "Courier New",
      "TextFontStyle": "StyleItalic",
      "TextFontWeight": "Normal"
    },
    {
      "ShapeId": 6,
      "TrackingId": 6044,
      "ShapeType": "Ellipse",
      "ShapeDimensions": [150, 150, 90, 45],
      "PenColor": "cyan",
      "PenWidth": 3,
      "PenStyle": "DotLine",
      "PenCapStyle": "FlatCap",
      "PenJoinStyle": "MiterJoin",
      "BrushColor": "blue",
      "BrushStyle": "Dense3Pattern"
    },
    {
      "ShapeId": 3,
      "TrackingId": 3933,
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
      "TrackingId": 4632,
      "ShapeType": "Rectangle",
      "ShapeDimensions": [300, 300, 100, 200],
      "PenColor": "lime",
      "PenWidth": 3,
      "PenStyle": "SolidLine",
      "PenCapStyle": "RoundCap",
      "PenJoinStyle": "RoundJoin",
      "BrushColor": "purple",
      "BrushStyle": "Dense6Pattern"
    },
    {
      "ShapeId": 5,
      "TrackingId": 5012,
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