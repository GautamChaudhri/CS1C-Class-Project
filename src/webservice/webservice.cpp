/**
 * @file webservice.cpp
 * @brief Implements the Crow web service for handling shapes, render area, user, and testimonial data.
 *
 * @details This web service provides the following endpoints, grouped by entity:
 *            - TEST GET "/"              : A test endpoint that returns a greeting.
 * 
 *            - Shapes Endpoints:
 *            - GET /shapes               : Returns the JSON-formatted shapes data from ../../database/shapes.json. 
 *            - POST /shapes              : Accepts JSON data to update the shapes file (../../database/shapes.json).
 *            - DELETE /shapes-all        : Clears all shapes data by truncating the shapes.json file.
 * 
 *            - Render Area Endpoints:
 *            - GET /render_area          : Returns the JSON-formatted render area data from ../../database/render_area.json.
 *            - POST /render_area         : Accepts JSON data to update the render area file (../../database/render_area.json).
 *            - DELETE /render_area-all   : Clears all render area data by truncating the render_area.json file.
 * 
 *            - Users Endpoints:
 *            - GET /users                : Returns the JSON-formatted user data from ../../database/users.json.
 *            - POST /users               : Accepts JSON data to update the user file (../../database/users.json).
 *            - DELETE /users-all         : Clears all user data by truncating the users.json file.
 * 
 *            - Testimonials Endpoints:
 *            - GET /testimonials         : Returns JSON-formatted testimonial data from ../../database/testimonials.json.
 *            - POST /testimonials        : Accepts JSON data to update the testimonials file (../../database/testimonials.json).
 *            - DELETE /testimonials      : Clears all testimonial data by truncating the testimonials.json file. (Note: Original was DELETE /testimonials, implying delete all)
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
      * @brief Retrieves shapes data.
      *
      * @details Reads the JSON data from "../../database/shapes.json", parses it using Crow's JSON parser, and 
      *          returns the data with the Content-Type header set to "application/json".
      */
     CROW_ROUTE(app, "/shapes").methods(crow::HTTPMethod::Get)
     ([](){
         try {
             auto shapes = get_json_file("../../database/shapes.json");
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
      * @brief Updates shapes.json with new shapes.
      *
      * @details Accepts a POST request with JSON data in the body and writes the contents
      *          to the file "../../database/shapes.json". If the file cannot be opened, a 500 response is returned.
      */
     CROW_ROUTE(app, "/shapes").methods(crow::HTTPMethod::Post)
     ([](const crow::request& req){
         std::filesystem::create_directory("../../database");
 
         std::ofstream outfile("../../database/shapes.json", std::ios::binary);
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
      * @brief Clears all shapes.
      *
      * @details Deletes the shapes.json file content by truncating the file,
      *          leaving it empty (an empty JSON array).
      */
     CROW_ROUTE(app, "/shapes-all").methods(crow::HTTPMethod::Delete)
     ([](){
         try {
             std::filesystem::create_directory("../../database");
             std::ofstream shapeFile("../../database/shapes.json", std::ios::trunc);
             if (!shapeFile) {
                 return crow::response(500, "Error clearing shapes file");
             }
             // Write an empty JSON array to keep valid format
             shapeFile << "[]";
             shapeFile.close();
             return crow::response(200, "All shapes cleared");
         }
         catch (const std::exception& exception) {
             return crow::response(500, exception.what());
         }
     });

     /**
      * @brief Retrieves render area data.
      *
      * @details Reads JSON data from "../../database/render_area.json", parses it using Crow's JSON parser,
      *          and returns the data with the Content-Type header set to "application/json".
      */
     CROW_ROUTE(app, "/render_area").methods(crow::HTTPMethod::Get)
     ([](){
         try {
             auto shapes = get_json_file("../../database/render_area.json");
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
      * @brief Updates the render area data.
      *
      * @details Accepts a POST request with JSON data and writes it to the file "../../database/render_area.json".
      *          Returns a 500 response if the file cannot be opened.
      */
     CROW_ROUTE(app, "/render_area").methods(crow::HTTPMethod::Post)
     ([](const crow::request& req){
         std::filesystem::create_directory("../../database");
 
         std::ofstream outfile("../../database/render_area.json", std::ios::binary);
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
      * @brief Clears all render area data.
      *
      * @details Deletes the render_area.json file content by truncating the file,
      *          leaving it empty (an empty JSON array).
      */
     CROW_ROUTE(app, "/render_area-all").methods(crow::HTTPMethod::Delete)
     ([](){
         try {
             std::filesystem::create_directory("../../database");
             std::ofstream raFile("../../database/render_area.json", std::ios::trunc);
             if (!raFile) {
                 return crow::response(500, "Error clearing render_area file");
             }
             // Write an empty JSON array to keep valid format
             raFile << "[]";
             raFile.close();
             return crow::response(200, "All render area data cleared");
         }
         catch (const std::exception& exception) {
             return crow::response(500, exception.what());
         }
     });

     /**
      * @brief Retrieves user account data.
      *
      * @details Reads the JSON data from "../../database/users.json", parses it, and returns it
      *          with Content-Type "application/json".
      */
     CROW_ROUTE(app, "/users").methods(crow::HTTPMethod::Get)
     ([](){
         try {
             auto users = get_json_file("../../database/users.json");
             crow::json::wvalue w = users;
             crow::response resp;
             resp.code = 200;
             resp.add_header("Content-Type", "application/json");
             resp.body = w.dump();
             return resp;
         }
         catch (const std::exception& exception) {
             return crow::response(500, exception.what());
         }
     });

     /**
      * @brief Updates users.json with new user data.
      *
      * @details Accepts a POST request with JSON body and writes it to "../../database/users.json".
      */
     CROW_ROUTE(app, "/users").methods(crow::HTTPMethod::Post)
     ([](const crow::request& req){
         std::filesystem::create_directory("../../database");
         std::ofstream outfile("../../database/users.json", std::ios::binary | std::ios::trunc);
         if (!outfile) {
             return crow::response(500, "Error saving user file");
         }
         outfile << req.body;
         outfile.close();
         return crow::response(200, "User file saved successfully");
     });

     /**
      * @brief Clears all user account data.
      *
      * @details Deletes the users.json file content by truncating it, leaving an empty JSON array.
      */
     CROW_ROUTE(app, "/users-all").methods(crow::HTTPMethod::Delete)
     ([](){
         try {
             std::filesystem::create_directory("../../database");
             std::ofstream userFile("../../database/users.json", std::ios::trunc);
             if (!userFile) {
                 return crow::response(500, "Error clearing user file");
             }
             userFile << "[]";
             userFile.close();
             return crow::response(200, "All user data cleared");
         }
         catch (const std::exception& exception) {
             return crow::response(500, exception.what());
         }
     });

    /**
     * @brief Retrieves testimonial data.
     *
     * @details Reads the JSON array from "../../database/testimonials.json",
     *          sets Content-Type to "application/json", and returns the data.
     *          Returns 500 if file cannot be opened or parsed.
     */
    CROW_ROUTE(app, "/testimonials").methods(crow::HTTPMethod::Get)
    ([](){
        try {
            auto testimonials = get_json_file("../../database/testimonials.json");
            crow::json::wvalue w = testimonials;
            crow::response resp;
            resp.code = 200;
            resp.add_header("Content-Type", "application/json");
            resp.body = w.dump();
            return resp;
        }
        catch (const std::exception& e) {
            return crow::response(500, std::string("Error retrieving testimonials: ") + e.what());
        }
    });

    /**
     * @brief Creates or updates testimonial data.
     *
     * @details Accepts a POST with JSON body containing an array of testimonials
     *          or a single testimonial object. Writes the body directly to
     *          "../../database/testimonials.json", creating the directory if needed.
     *          Returns 200 on success or 500 on failure.
     */
    CROW_ROUTE(app, "/testimonials").methods(crow::HTTPMethod::Post)
    ([](const crow::request& req){
        try {
            std::filesystem::create_directory("../../database");
            std::ofstream outfile("../../database/testimonials.json", std::ios::binary | std::ios::trunc);
            if (!outfile) {
                return crow::response(500, "Error opening testimonials file for writing");
            }
            outfile << req.body;
            outfile.close();
            return crow::response(200, "Testimonials saved successfully");
        }
        catch (const std::exception& e) {
            return crow::response(500, std::string("Error saving testimonials: ") + e.what());
        }
    });

    /**
     * @brief Clears all testimonial data.
     *
     * @details Truncates the testimonials.json file, writing an empty JSON array.
     *          Returns 200 on success or 500 on failure.
     */
    CROW_ROUTE(app, "/testimonials").methods(crow::HTTPMethod::Delete) // Assuming this means delete all testimonials
    ([](){
        try {
            std::filesystem::create_directory("../../database");
            std::ofstream file("../../database/testimonials.json", std::ios::trunc);
            if (!file) {
                return crow::response(500, "Error clearing testimonials file");
            }
            file << "[]";
            file.close();
            return crow::response(200, "All testimonials cleared");
        }
        catch (const std::exception& e) {
            return crow::response(500, std::string("Error clearing testimonials: ") + e.what());
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
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string contents = buffer.str();

    if (contents.empty())
        return crow::json::load("[]");

    auto jsonData = crow::json::load(contents);
    if (!jsonData)
        throw std::runtime_error("Failed to parse file: " + path);
    
    return jsonData;
}