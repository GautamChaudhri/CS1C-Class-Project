#include <QCoreApplication>
#include <QObject>
#include "ApiClient.h"
//#include "ApiHandler.h"   | i'm dumb and made this when we don't need it
#include "Parser.h"
#include "UserManager.h"

void OnGoodGetResponseTest(const std::string &json);
void OnBadGetResponseTest(const std::string &errorMsg);
void OnGoodPostResponseTest();
void OnBadPostResponseTest(const std::string &errorMsg);
ApiClient* GetConnectedClient();

//For testing
std::string GetUsersTestString();
std::string GetShapeTestString();
std::string GetRenderAreaTestString();

//Global accesss for app, client, and parser
QCoreApplication* pApp = nullptr;
ApiClient* pClient = nullptr;
Parser parse;

//Webservice must be up and running for main to work
int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    pApp = &app;

    //Testing gauntlet point 1
    std::cout << "Starting Test Gauntlet! Test Point 1: Get users\n";
    UserManager manager;

    //Test point 2
    ApiClient* client = GetConnectedClient();
    pClient = client;
    //client->PostUsers(userTest);
    std::cout << "Test Point 2: Get render area\n";
    client->GetRenderArea();

    // Start the Qt event loop; this loop will run until app.quit() is called.
    return app.exec();
}

void OnGoodGetResponseTest(const std::string &json) {
  //Test point 2 cont.
  std::cout << "Received JSON from webservice:\n" << json << std::endl << std::endl;

  //Test point 3
  std::cout << "Test point 3: convert json to vector of shapes\n";
  alpha::vector<Shape*> shapes = parse.JsonToShapes(json);
  std::cout << "Shapes in vector:\n";
  parse.PrintShapeVector(shapes);

  //Test point 4
  std::cout << "Test point 4: convert vector of shapes to json\n";
  std::string jsonShapes = parse.ShapesToJson(shapes);
  std::cout << "Outputting new JSON:\n";
  std::cout << jsonShapes << std::endl << std::endl;

  //Test point 5
  std::cout << "Test point 5: Post endpoint\n";
  pClient->PostShapes(jsonShapes);
}

void OnBadGetResponseTest(const std::string &errorMsg) {
    std::cerr << "Error: " << errorMsg << std::endl << std::endl;
    pApp->quit();
}

void OnGoodPostResponseTest() {
    //Test point 5 cont.
    std::cout << "Data Received by webservice successfully!\n";
    std::cout << "Finish Test Gauntlet!\n";
    pApp->quit();
}

void OnBadPostResponseTest(const std::string &errorMsg) {
    std::cerr << "Error: " << errorMsg << std::endl;
    pApp->quit();
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

// For testing: ten random UserAccount JSON objects
std::string GetUsersTestString() {
  return R"([
  {
    "username": "alice",
    "password": "Wonderland1!",
    "admin": true
  },
  {
    "username": "bob",
    "password": "Builder#22",
    "admin": false
  },
  {
    "username": "carol",
    "password": "C@rol2025",
    "admin": true
  },
  {
    "username": "dave",
    "password": "davE_pw_3",
    "admin": false
  },
  {
    "username": "eve",
    "password": "3v3_secret",
    "admin": true
  },
  {
    "username": "frank",
    "password": "FrankPass4",
    "admin": false
  },
  {
    "username": "grace",
    "password": "Gr@ceful5",
    "admin": false
  },
  {
    "username": "heidi",
    "password": "heidi-6pwd",
    "admin": true
  },
  {
    "username": "ivan",
    "password": "Ivan_pw7",
    "admin": false
  },
  {
    "username": "judy",
    "password": "JuDy!2025",
    "admin": false
  }
])";
}

std::string GetShapeTestString() {
    return R"([[
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
    },
    {
      "ShapeId": 2,
      "TrackerId": null,
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
      "TrackerId": null,
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
      "TrackerId": null,
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
      "TrackerId": null,
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
      "TrackerId": null,
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
      "TrackerId": null,
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
      "TrackerId": null,
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
