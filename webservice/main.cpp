//main.cpp
#include <crow.h>  // Located in crow/include/crow.h  || Check crow guide if this shows error and using VS Code
#include <crow/json.h>
#include <string>
#include <fstream>
#include <filesystem>

//Prototypes
crow::json::rvalue get_json_file(const std::string& path);

int main()
{
    crow::SimpleApp app;

    //Test endpoint 1
    CROW_ROUTE(app, "/")([](){
        return "Hello, Crow!";
    });

    //Test endpoint 2
    CROW_ROUTE(app, "/upload-shapes").methods(crow::HTTPMethod::Post)
    ([](const crow::request& req){
        
        std::filesystem::create_directory("../database");

        std::ofstream outfile("../database/shapes.txt", std::ios::binary);
        if (!outfile)
        {
            return crow::response(500, "Error saving file");
        }

        // Write the content received (assuming req.body contains the file data)
        outfile << req.body;
        outfile.close();
        return crow::response(200, "File saved successfully");
    });


    //Returns all possible shapes that can be rendered (user story 3 & 4)
    CROW_ROUTE(app, "/shapes").methods(crow::HTTPMethod::Get)
    ([](){
        try {
            auto shapes = get_json_file("../database/shapes.json");
            crow::json::wvalue w = shapes;

            crow::response resp;
            resp.code = 200;
            resp.add_header("Content-Type", "application/json");    //tells client json information incoming
            resp.body = w.dump();
            return resp;
        }
        catch (const std::exception& exception) {
            return crow::response(500, exception.what());
        }
    });

    // Run the server on port 8080
    app.port(8080).multithreaded().run();
    return 0;
}

//Returns the data from a json file in json format for get endpoints
crow::json::rvalue get_json_file(const std::string& path) {
    std::ifstream file(path);
    if (!file) 
        throw std::runtime_error("Failed to open file: " + path);
    
    //Put data into a stream object
    std::stringstream buffer;
    buffer << file.rdbuf();

    //Parse data with crow's json parser
    auto jsonData = crow::json::load(buffer.str());
    if (!jsonData)
        throw std::runtime_error("Failed to parse file: " + path);
    
    return jsonData;
}

    //Come back after parser is created
    // CROW_ROUTE(app, "/upload-shapes-file").methods(crow::HTTPMethod::Post)
    // ([](const crow::request& req){
    //     //When file comes in, two options
    //     std::filesystem::create_directory("database");
    //     std::fstream shapeFile("database/shapes.txt", std::ios::app);
    //     if (!shapeFile)
    //         return crow::response(500, "Error saving file");
    //     //1: If shapes.txt is empty, add whole file without parsing
    //     else if (std::filesystem::file_size("database/shapes.txt") == 0)
    //         shapeFile << req.body;
    //     //2: If shapes.txt is not empty, parse through shapes.txt and selectively add only new shapes
    //     else {
    //         //Converts a string object into an input stream like cin
    //         std::istringstream iss(req.body);
    //         std::string line;
    //         getline(iss, line);
    //     }
    //     shapeFile.close();
    //     return crow::response(200, "File saved successfully");
    // });