/**
 * @file webservice.cpp
 * @brief Implements the Crow web service for handling shapes and render area data.
 *
 * @details This web service provides the following endpoints:
 *            - GET "/"             : A test endpoint that returns a greeting.
 *            - POST /shapes        : Accepts JSON data to update the shapes file (../database/shapes.json).
 *            - GET /shapes         : Returns the JSON-formatted shapes data from ../database/shapes.json.
 *            - DELETE /shape       : Deletes a shape (identified by ShapeId) from the shapes file.
 *            - POST /render_area   : Accepts JSON data to update the render area file (../database/render_area.json).
 *            - GET /render_area    : Returns the JSON-formatted render area data from ../database/render_area.json.
 *
 * @note Uses the Crow framework for handling HTTP requests. Make sure the database directory exists or is created.
 */

 #include <crow.h>  // Located in crow/include/crow.h 
 #include <crow/json.h>
 #include <string>
 #include <fstream>
 #include <filesystem>
 
 //Prototypes
 crow::json::rvalue get_json_file(const std::string& path);
 
 int main()
 {
     crow::SimpleApp app;
 
     /**
      * @brief Test endpoint.
      *
      * @details Returns a simple greeting message to verify that the web service is running.
      */
     CROW_ROUTE(app, "/")([](){
         return "Hello, Crow!";
     });
 
     /**
      * @brief Updates shapes.json with new shapes.
      *
      * @details Accepts a POST request with JSON data in the body and writes the contents
      *          to the file "../database/shapes.json". If the file cannot be opened, a 500 response is returned.
      */
     CROW_ROUTE(app, "/shapes").methods(crow::HTTPMethod::Post)
     ([](const crow::request& req){
         std::filesystem::create_directory("../database");
 
         std::ofstream outfile("../database/shapes.json", std::ios::binary);
         if (!outfile)
         {
             return crow::response(500, "Error saving file");
         }
 
         // Write the content received (assuming req.body contains the file data)
         outfile << req.body;
         outfile.close();
         return crow::response(200, "File saved successfully");
     });
 
     /**
      * @brief Retrieves shapes data.
      *
      * @details Reads the JSON data from "../database/shapes.json", parses it using Crow's JSON parser, and 
      *          returns the data with the Content-Type header set to "application/json".
      */
     CROW_ROUTE(app, "/shapes").methods(crow::HTTPMethod::Get)
     ([](){
         try {
             auto shapes = get_json_file("../database/shapes.json");
             crow::json::wvalue w = shapes;
 
             crow::response resp;
             resp.code = 200;
             resp.add_header("Content-Type", "application/json");    // Tells client JSON information is incoming
             resp.body = w.dump();
             return resp;
         }
         catch (const std::exception& exception) {
             return crow::response(500, exception.what());
         }
     });
 
     /**
      * @brief Deletes a shape.
      *
      * @details Parses a DELETE request that provides a JSON body with a "ShapeId" key. The function removes the shape
      *          with the matching ShapeId from "../database/shapes.json" and writes the updated list back to the file.
      *          Returns a 404 response if the ShapeId is not found.
      */
     CROW_ROUTE(app, "/shape").methods(crow::HTTPMethod::Delete)
     ([](const crow::request& req){
         try {
             // Parse the request to get the ShapeId to delete
             auto deleteTarget = crow::json::load(req.body);
             if (!deleteTarget || !deleteTarget.has("ShapeId"))
                 return crow::response(400, "Missing or invalid ShapeId");
             int targetID = deleteTarget["ShapeId"].i();
 
             // Parse existing shapes to find targetID
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
                 // Overwrite shapes.json with new shapes which has the target shape missing
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
 
     /**
      * @brief Updates the render area data.
      *
      * @details Accepts a POST request with JSON data and writes it to the file "../database/render_area.json".
      *          Returns a 500 response if the file cannot be opened.
      */
     CROW_ROUTE(app, "/render_area").methods(crow::HTTPMethod::Post)
     ([](const crow::request& req){
         std::filesystem::create_directory("../database");
 
         std::ofstream outfile("../database/render_area.json", std::ios::binary);
         if (!outfile)
         {
             return crow::response(500, "Error saving file");
         }
 
         // Write the content received (assuming req.body contains the file data)
         outfile << req.body;
         outfile.close();
         return crow::response(200, "File saved successfully");
     });
 
     /**
      * @brief Retrieves render area data.
      *
      * @details Reads JSON data from "../database/render_area.json", parses it using Crow's JSON parser,
      *          and returns the data with the Content-Type header set to "application/json".
      */
     CROW_ROUTE(app, "/render_area").methods(crow::HTTPMethod::Get)
     ([](){
         try {
             auto shapes = get_json_file("../database/render_area.json");
             crow::json::wvalue w = shapes;
 
             crow::response resp;
             resp.code = 200;
             resp.add_header("Content-Type", "application/json");    // Tells client JSON information is incoming
             resp.body = w.dump();
             return resp;
         }
         catch (const std::exception& exception) {
             return crow::response(500, exception.what());
         }
     });
 
     // Run the server on port 8080 using multiple threads
     app.port(8080).multithreaded().run();
     return 0;
 }
 
 /**
  * @brief Reads and parses a JSON file.
  *
  * @details Opens the file at the specified path, loads its contents into a stringstream,
  *          and uses Crow's JSON parser to convert the data into a crow::json::rvalue.
  *          Throws a std::runtime_error if the file cannot be opened or parsed.
  *
  * @param path The file system path to the JSON file.
  * @return crow::json::rvalue The parsed JSON data.
  */
 crow::json::rvalue get_json_file(const std::string& path) {
     std::ifstream file(path);
     if (!file) 
         throw std::runtime_error("Failed to open file: " + path);
     
     // Put file data into a stringstream
     std::stringstream buffer;
     buffer << file.rdbuf();
 
     // Parse data with Crow's JSON parser
     auto jsonData = crow::json::load(buffer.str());
     if (!jsonData)
         throw std::runtime_error("Failed to parse file: " + path);
     
     return jsonData;
 }