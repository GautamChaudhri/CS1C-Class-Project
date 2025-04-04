
//main.cpp
#include <crow.h>  // Crow headers are located in crow/include/crow

int main()
{
    crow::SimpleApp app;

    // Define a simple GET endpoint at "/"
    CROW_ROUTE(app, "/")([](){
        return "Hello, Crow!";
    });

    // Run the server on port 8080
    app.port(8080).multithreaded().run();
    return 0;
}