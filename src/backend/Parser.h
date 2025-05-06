#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <cctype>
#include <QVector>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <string>
#include "../objects/vector.h"
#include "../objects/all_shapes.h"
#include "UserAccount.h"
#include "Testimonial.h"

/**
 * @brief Provides functionality for parsing JSON data to C++ objects and vice-versa.
 *
 * @details The Parser class handles the serialization and deserialization of various
 *          data structures used in the application, such as Shapes, UserAccounts,
 *          and Testimonials, converting them to and from JSON string representations.
 *          It includes methods for both forward parsing (JSON to object) and
 *          reverse parsing (object to JSON). This class does not store any data itself
 *          and its copy/move operations are disabled.
 */
class Parser {
public:
    /** @brief Default constructor. Initializes a Parser object. */
    Parser() = default;
    /** @brief Default destructor. Cleans up resources used by the Parser object. */
    ~Parser() = default;

    //Disable copying and moving
    /** @brief Deleted copy constructor to prevent copying Parser objects. */
    Parser(const Parser&) = delete;
    /** @brief Deleted copy assignment operator to prevent copying Parser objects. */
    Parser& operator=(const Parser&) = delete;
    /** @brief Deleted move constructor to prevent moving Parser objects. */
    Parser(Parser&&) = delete;
    /** @brief Deleted move assignment operator to prevent moving Parser objects. */
    Parser& operator=(Parser&&) = delete;

    /**
     * @brief Prints properties of shapes in a vector to the console.
     * @details Iterates through a vector of Shape pointers and prints their ID,
     *          TrackerId, and ShapeType to standard output. Primarily for debugging purposes.
     * @param shapes A constant reference to an alpha::vector of Shape pointers.
     */
    void PrintShapeVector(const alpha::vector<Shape*> &shapes);

    /**
     * @brief Converts a JSON string representation into a vector of Shape objects.
     * @details This is a forward parsing method that takes a JSON string,
     *          parses it, and constructs a vector of dynamically allocated Shape objects.
     * @param json A constant reference to a string containing the JSON data for shapes.
     * @return An alpha::vector of Shape pointers, each pointing to an instantiated Shape object.
     * @throws std::runtime_error If the JSON string is malformed or parsing fails.
     */
    alpha::vector<Shape*> JsonToShapes(const std::string& json);

    /**
     * @brief Converts a vector of Shape pointers into a JSON string representation.
     * @details This is a reverse parsing method that takes a vector of Shape objects
     *          and serializes them into a JSON formatted string.
     * @param shapes A constant reference to an alpha::vector of Shape pointers.
     * @return A string formatted in JSON containing all key:value pairs for the shapes.
     */
    std::string ShapesToJson(const alpha::vector<Shape*>& shapes);

    /**
     * @brief Converts a JSON string representation into a vector of UserAccount objects.
     * @details This forward parsing method processes a JSON string to create UserAccount objects.
     * @param json A constant reference to a string containing the JSON data for user accounts.
     * @return An alpha::vector of UserAccount pointers.
     * @throws std::runtime_error If the JSON string is malformed or essential user data is missing.
     */
    alpha::vector<UserAccount*> JsonToUsers(const std::string& json);

    /**
     * @brief Converts a vector of UserAccount pointers into a JSON string representation.
     * @details This reverse parsing method serializes UserAccount objects into a JSON string.
     * @param users A constant reference to an alpha::vector of UserAccount pointers.
     * @return A string formatted in JSON representing the user accounts.
     */
    std::string UsersToJson(const alpha::vector<UserAccount*>& users);

    /**
     * @brief Converts a JSON string representation into a QVector of Testimonial objects.
     * @details This static forward parsing method uses Qt's JSON utilities to parse testimonials.
     * @param json A constant reference to a string containing the JSON data for testimonials.
     * @return A QVector of Testimonial objects.
     * @throws std::runtime_error If JSON parsing fails or the top-level structure is not an array.
     */
    static QVector<Testimonial> JsonToTestimonials(const std::string& json);

    /**
     * @brief Converts a QVector of Testimonial objects into a JSON string representation.
     * @details This static reverse parsing method uses Qt's JSON utilities to serialize testimonials.
     * @param testimonials A constant reference to a QVector of Testimonial objects.
     * @return A string formatted in JSON representing the testimonials.
     */
    static std::string TestimonialsToJson(const QVector<Testimonial>& testimonials);

private:
    /*==================================== Forward Parser Subroutines ============================================*/
    /**
     * @brief Internal accumulator structure for parsing shape data from JSON.
     * @details This structure temporarily holds the properties of a shape as they are
     *          parsed from a JSON object. It allows for jumbled key-value pairs
     *          and converts string values to their appropriate C++ types before a
     *          final Shape object is constructed.
     */
    struct MorphicShape {
        std::string shapeType = "";             /**< @brief The type of the shape (e.g., "Line", "Circle"). */
        int shapeId = 0;                        /**< @brief The unique identifier for the shape type. */
        int trackerId = 0;                      /**< @brief A tracking ID for the shape instance. */
        alpha::vector<int> shapeDimensions;     /**< @brief A vector holding the geometric dimensions of the shape. */
        QPen pen = QPen();                      /**< @brief The QPen object defining the shape's outline properties. */
        QBrush brush = QBrush();                /**< @brief The QBrush object defining the shape's fill properties. */
        QPoint coords = QPoint();               /**< @brief The primary coordinates (e.g., top-left point) of the shape. */

        QString textString;                     /**< @brief The string content for Text shapes. */
        GlobalColor textColor;                  /**< @brief The color of the text for Text shapes. */
        QFont font;                             /**< @brief The QFont object for Text shapes. */
        AlignmentFlag textAlignment;            /**< @brief The alignment for Text shapes. */
    };

    /**
     * @brief Internal accumulator structure for parsing user account data from JSON.
     * @details This structure temporarily holds the properties of a user account as they are
     *          parsed from a JSON object, along with flags to track if fields were found.
     */
    struct RawUser {
            QString username;                   /**< @brief The username of the user. */
            QString password;                   /**< @brief The password of the user. */
            bool    admin       = false;        /**< @brief Flag indicating if the user has admin privileges. */
            bool    hasUsername = false;        /**< @brief Flag indicating if the username was found during parsing. */
            bool    hasPassword = false;        /**< @brief Flag indicating if the password was found during parsing. */
            bool    hasAdmin    = false;        /**< @brief Flag indicating if the admin status was found during parsing. */
        };

    /**
     * @brief Parses a single JSON object (data within '{}') into a MorphicShape.
     * @details This helper function processes one JSON object from the input string,
     *          extracting key-value pairs and populating a MorphicShape accumulator.
     * @param json The JSON string being parsed.
     * @param index A reference to the current parsing index within the JSON string, modified by the function.
     * @return A MorphicShape object containing the parsed data.
     * @throws std::runtime_error If the JSON object is malformed.
     */
    MorphicShape ParseJsonObject(const std::string json, size_t &index);

    /**
     * @brief Updates a MorphicShape accumulator with a parsed key-value pair.
     * @details Converts the string `value` to its appropriate C++ type based on the `key`
     *          and stores it in the corresponding member of the `tempShape` accumulator.
     * @param key The JSON key as a string.
     * @param value The JSON value as a string.
     * @param tempShape A reference to the MorphicShape accumulator to be updated.
     * @throws std::runtime_error If the key is unknown or the value is invalid for the key.
     */
    void UpdateAccumulator(const std::string &key, const std::string &value, MorphicShape &tempShape);

    /**
     * @brief Constructs a concrete Shape object from a populated MorphicShape accumulator.
     * @details Based on the `shapeId` in `tempShape`, this function dynamically allocates
     *          and initializes the appropriate derived Shape object (e.g., Line, Circle).
     * @param tempShape The MorphicShape object containing the data for the new shape.
     * @return A pointer to the newly instantiated Shape object, or nullptr if construction fails.
     */
    Shape* BuildShape(MorphicShape tempShape);

    /**
     * @brief Advances the parsing index past any whitespace characters.
     * @details Modifies `index` to point to the next non-whitespace character in the `json` string.
     * @param json The JSON string being parsed.
     * @param index A reference to the current parsing index, modified by the function.
     */
    void SkipWhitespace(const std::string& json, size_t& index);

    /**
     * @brief Extracts a JSON key (a string enclosed in double quotes) from the input string.
     * @details Assumes `index` is at the opening double quote of the key. Modifies `index`
     *          to point immediately after the closing double quote of the key.
     * @param json The JSON string being parsed.
     * @param index A reference to the current parsing index, modified by the function.
     * @return The extracted key as a std::string.
     */
    std::string ExtractKey(const std::string& json, size_t &index);

    /**
     * @brief Extracts a JSON value from the input string.
     * @details Handles strings, numbers, arrays, and boolean literals. Modifies `index`
     *          to point after the extracted value.
     * @param json The JSON string being parsed.
     * @param index A reference to the current parsing index, modified by the function.
     * @return The extracted value as a std::string.
     * @throws std::runtime_error If the value type is unexpected.
     */
    std::string ExtractValue(const std::string& json, size_t &index);

    /**
     * @brief Extracts an integer value from the JSON string.
     * @details Assumes `index` is at the first digit of the integer. Modifies `index`
     *          to point after the last digit of the integer.
     * @param json The JSON string being parsed.
     * @param index A reference to the current parsing index, modified by the function.
     * @return The extracted integer as a std::string.
     */
    std::string ExtractInteger(const std::string& json, size_t &index);

    /**
     * @brief Extracts a JSON array (content within '[]') as a string.
     * @details Assumes `index` is at the opening bracket of the array. Modifies `index`
     *          to point after the closing bracket of the array.
     * @param json The JSON string being parsed.
     * @param index A reference to the current parsing index, modified by the function.
     * @return The extracted array (including brackets) as a std::string.
     * @throws std::runtime_error If the closing bracket is missing.
     */
    std::string ExtractArray(const std::string& json, size_t &index);

    /**
     * @brief Extracts a JSON literal (true, false, null) as a string.
     * @details Assumes `index` is at the first character of the literal. Modifies `index`
     *          to point after the last character of the literal.
     * @param json The JSON string being parsed.
     * @param index A reference to the current parsing index, modified by the function.
     * @return The extracted literal as a std::string.
     */
    std::string ExtractLiteral(const std::string& json, size_t& index);
    
    /**
     * @brief Converts a string representation of a JSON array of integers into an alpha::vector<int>.
     * @details Parses a string like "[20, 32, 41, 64]" into a vector of integers.
     * @param value The string representation of the integer array.
     * @return An alpha::vector<int> containing the parsed integers.
     * @throws std::runtime_error If the string format is invalid.
     */
    alpha::vector<int> StringToVector(const std::string &value);

    /*==================================== Reverse Parser Subroutines ============================================*/

    /**
     * @brief Appends common shape properties (ID, Type, Dimensions, Pen properties) to a JSON string.
     * @details This helper function is used during the serialization of shapes to JSON.
     *          It formats 9 common key-value pairs.
     * @param shape A constant pointer to the Shape object to serialize.
     * @return A std::string containing the JSON representation of common shape data.
     */
    std::string AppendCommonShapeData(const Shape* shape);

    /**
     * @brief Appends QBrush properties (BrushColor, BrushStyle) to a JSON string.
     * @details This helper function is used for shapes that have fill properties.
     * @param shape A constant pointer to the Shape object whose brush data is to be serialized.
     * @return A std::string containing the JSON representation of brush data.
     */
    std::string AppendBrushData(const Shape* shape);

    /**
     * @brief Appends all properties specific to Text objects to a JSON string.
     * @details Serializes properties like TextString, PointSize, Color, Alignment, Font.
     * @param shape A constant pointer to the Shape object, expected to be a Text object.
     * @return A std::string containing the JSON representation of text data.
     * @throws std::runtime_error If the provided shape cannot be cast to Text.
     */
    std::string AppendTextData(const Shape* shape);

    /**
     * @brief Gets the geometric dimensions of a shape as a JSON array string.
     * @details The specific dimensions depend on the shape type (e.g., coordinates for Line,
     *          points for Polyline/Polygon, x,y,length,width for Rectangle).
     * @param shape A constant pointer to the Shape object.
     * @return A std::string representing a JSON array of the shape's dimensions.
     * @throws std::runtime_error If the shape type is unknown or casting fails.
     */
    std::string GetShapeDimensions(const Shape* shape);

    /**
     * @brief Converts a QColor object to its string representation (e.g., "red", "blue").
     * @param objectColor The QColor to be converted.
     * @return A std::string representing the color name.
     * @throws std::runtime_error If the color is not one of the predefined known colors.
     */
    std::string GetColor(const QColor &objectColor);

    /**
     * @brief Gets the pen style of a shape as a string (e.g., "SolidLine", "DashLine").
     * @param shape A constant pointer to the Shape object.
     * @return A std::string representing the pen style.
     * @throws std::runtime_error If the pen style is unknown.
     */
    std::string GetPenStyle(const Shape* shape);

    /**
     * @brief Gets the pen cap style of a shape as a string (e.g., "FlatCap", "RoundCap").
     * @param shape A constant pointer to the Shape object.
     * @return A std::string representing the pen cap style.
     * @throws std::runtime_error If the pen cap style is unknown.
     */
    std::string GetPenCapStyle(const Shape* shape);

    /**
     * @brief Gets the pen join style of a shape as a string (e.g., "MiterJoin", "BevelJoin").
     * @param shape A constant pointer to the Shape object.
     * @return A std::string representing the pen join style.
     * @throws std::runtime_error If the pen join style is unknown.
     */
    std::string GetPenJoinStyle(const Shape* shape);

    /**
     * @brief Gets the brush style of a shape as a string (e.g., "SolidPattern", "NoBrush").
     * @param shape A constant pointer to the Shape object.
     * @return A std::string representing the brush style.
     * @throws std::runtime_error If the brush style is unknown.
     */
    std::string GetBrushStyle(const Shape* shape);

    /**
     * @brief Gets the text alignment of a Text object as a string (e.g., "AlignLeft", "AlignCenter").
     * @param text A constant pointer to the Text object.
     * @return A std::string representing the text alignment.
     * @throws std::runtime_error If the alignment flag is unknown.
     */
    std::string GetAlignmentFlag(const Text* text);

    /**
     * @brief Gets the font style of a Text object as a string (e.g., "StyleNormal", "StyleItalic").
     * @param text A constant pointer to the Text object.
     * @return A std::string representing the font style.
     * @throws std::runtime_error If the font style is unknown.
     */
    std::string GetFontStyle(const Text* text);

    /**
     * @brief Gets the font weight of a Text object as a string (e.g., "Normal", "Bold").
     * @param text A constant pointer to the Text object.
     * @return A std::string representing the font weight.
     * @throws std::runtime_error If the font weight is unknown.
     */
    std::string GetFontWeight(const Text* text);

    /**
     * @brief Updates a RawUser accumulator with a parsed key-value pair for user data.
     * @details Converts the string `value` to its appropriate C++ type based on the `key`
     *          (username, password, admin) and stores it in the `acc` accumulator.
     *          Also sets flags in `acc` to indicate which fields were found.
     * @param key The JSON key as a string.
     * @param value The JSON value as a string.
     * @param acc A reference to the RawUser accumulator to be updated.
     * @throws std::runtime_error If the value for 'admin' is not "true" or "false".
     */
    static void   UpdateUserAccumulator(const std::string& key, const std::string& value, RawUser& acc);
};

#endif // PARSER_H
