//main.cpp
#include <crow.h>  // Crow headers are located in crow/include/crow
#include <string>
#include <fstream>
#include <filesystem>
using namespace std;

int main()
{
    crow::SimpleApp app;

    
    CROW_ROUTE(app, "/")([](){
        return "Hello, Crow!";
    });

    
    CROW_ROUTE(app, "/upload-shapes").methods(crow::HTTPMethod::Post)
    ([](const crow::request& req){
        
        filesystem::create_directory("database");

        std::ofstream outfile("database/shapes.txt", ios::binary);
        if (!outfile)
        {
            return crow::response(500, "Error saving file");
        }

        // Write the content received (assuming req.body contains the file data)
        outfile << req.body;
        outfile.close();
        return crow::response(200, "File saved successfully");
    });


    CROW_ROUTE(app, "/upload-shapes-file").methods(crow::HTTPMethod::Post)
    ([](const crow::request& req){
        //When file comes in, two options
        filesystem::create_directory("database");
        fstream shapeFile("database/shapes.txt", ios::app);
        if (!shapeFile)
            return crow::response(500, "Error saving file");
        //1: If shapes.txt is empty, add whole file without parsing
        else if (filesystem::file_size("database/shapes.txt") == 0)
            shapeFile << req.body;
        //2: If shapes.txt is not empty, parse through shapes.txt and selectively add only new shapes
        else {
            //Converts a string object into an input stream like cin
            istringstream iss(req.body);
            string line;

            getline(iss, line);

        }

        
        
    

        
        shapeFile.close();
        return crow::response(200, "File saved successfully");
    });


    // Run the server on port 8080
    app.port(8080).multithreaded().run();
    return 0;
}