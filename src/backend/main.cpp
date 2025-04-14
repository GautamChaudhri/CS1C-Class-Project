#include <iostream>
#include <QCoreApplication>
#include <QObject>
#include "ApiClient.h"
//#include "ApiHandler.h"   | i'm dumb and made this when we don't need it
#include "Parser.h"

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
ApiClient* pClient = nullptr;
Parser parse;

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
    pClient = client;

    std::string testStr = GetRenderAreaTestString();
    client->PostShapes(testStr);
    
    //testStr = GetRenderAreaTestString();
    //client->GetShapes();

    //std::string testStr = GetRenderAreaTestString();
    //alpha::vector<Shape*> shapes = parse.JsonToShapes(testStr);
    //parse.PrintShapeVector(shapes);

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
    std::cout << "Received JSON from webservice!" << std::endl << std::endl;
    std::string jsonStr = json.toStdString();
    alpha::vector<Shape*> shapes = parse.JsonToShapes(jsonStr);
    std::cout << "Print Vector of Shapes*:" << std::endl;
    parse.PrintShapeVector(shapes);
    //pApp->quit();
}

void OnBadGetResponseTest(const QString &errorMsg) {
    std::cerr << "Error: " << errorMsg.toStdString() << std::endl << std::endl;
    //pApp->quit();
}

void OnGoodPostResponseTest() {
    std::cout << "Data Received by webservice successfully!\n";
    pClient->GetShapes();
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
      "TrackerId": null,
      "ShapeType": "Line",
      "ShapeDimensions": [20, 90, 100, 20],
      "PenColor": "blue",
      "PenWidth": 2,
      "PenStyle": "DashDotLine",
      "PenCapStyle": "FlatCap",
      "PenJoinStyle": "MiterJoin"
    }
  ])";
}

std::string GetRenderAreaTestString() {
    return R"([
    {
      "ShapeId": 1,
      "TrackerId": 1320,
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
      "ShapeId": 3,
      "TrackerId": 3619,
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
      "TrackerId": 4383,
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
      "TrackerId": 5524,
      "ShapeType": "Square",
      "ShapeDimensions": [500, 500, 80],
      "PenColor": "black",
      "PenWidth": 1,
      "PenStyle": "SolidLine",
      "PenCapStyle": "RoundCap",
      "PenJoinStyle": "RoundJoin",
      "BrushColor": "magenta",
      "BrushStyle": "VerPattern"
    },
    {
      "ShapeId": 6,
      "TrackerId": 6852,
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
      "TrackerId": 7901,
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
      "TrackerId": 8675,
      "ShapeType": "Text",
      "ShapeDimensions": [100, 600, 300, 40],
      "TextString": "Sample Text A",
      "TextColor": "blue",
      "TextAlignment": "AlignCenter",
      "TextPointSize": 14,
      "TextFontFamily": "Arial",
      "TextFontStyle": "StyleNormal",
      "TextFontWeight": "Bold"
    },
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
