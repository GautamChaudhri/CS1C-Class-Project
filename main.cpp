//main.cpp
#include <crow.h>  // Crow headers are located in crow/include/crow
#include <fstream>
#include <filesystem>

int main()
{
    crow::SimpleApp app;

    // Define a simple GET endpoint at "/"
    CROW_ROUTE(app, "/")([](){
        return "Hello, Crow!";
    });

    // POST endpoint to receive and save shapes.txt
    CROW_ROUTE(app, "/upload-shapes").methods(crow::HTTPMethod::Post)
    ([](const crow::request& req){
        // Optional: Ensure the directory "uploads" exists
        std::filesystem::create_directory("database");

        // Open the file "shapes.txt" in the "uploads" directory
        std::ofstream outfile("database/shapes.txt", std::ios::binary);
        if (!outfile)
        {
            return crow::response(500, "Error saving file");
        }
        // Write the content received (assuming req.body contains the file data)
        outfile << req.body;
        outfile.close();
        return crow::response(200, "File saved successfully");
    });

    // Run the server on port 8080
    app.port(8080).multithreaded().run();
    return 0;
}