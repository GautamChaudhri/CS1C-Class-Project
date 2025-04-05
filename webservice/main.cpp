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

    //Deletes a shape (user story 6)
    CROW_ROUTE(app, "/shape").methods(crow::HTTPMethod::Delete)
    ([](const crow::request& req){
        try {
            //Parse the request to get the ShapeId to delete
            auto deleteTarget = crow::json::load(req.body);
            if (!deleteTarget || !deleteTarget.has("ShapeId"))
                return crow::response(400, "Missing or invalid ShapeId");
            int targetID = deleteTarget["ShapeId"].i();

            //Parse existing shapes to find targetID
            auto allShapes = get_json_file("../database/shapes.json");
            crow::json::wvalue newShapesList;
            // Initialize as JSON object with a "shapes" array
            newShapesList["shapes"] = crow::json::wvalue::list();

            bool found = false;
            auto& shapesArray = newShapesList["shapes"];
            for (size_t i = 0; i < allShapes.size(); ++i) {
                if (allShapes[i]["ShapeId"].i() != targetID) {
                    // Append to array by index
                    shapesArray[shapesArray.size()] = allShapes[i];
                } else
                    found = true;
            }

            if (!found)
                return crow::response(404, "ShapeId not found in database");
            else {
                //Overwrite shapes.json with new shapes which has the target shape missing
                std::ofstream shapeFile("../database/shapes.json");
                shapeFile << newShapesList["shapes"].dump(4);
                shapeFile.close();
                return crow::response(200, "Shape deleted successfully");
            }
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

