#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <cctype>
#include "../objects/vector.h"
#include "../objects/all_shapes.h"

class Parser {
public:
    //Use default constructor/destructor as this class doesn't store any data
    Parser() = default;
    ~Parser() = default;

    //Disable copying and moving
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    Parser(Parser&&) = delete;
    Parser& operator=(Parser&&) = delete;

    /**
     * @brief This function takes in a vector of Shape pointers and prints
     *        some of their primitive data type properties.
     * 
     * @param shapes - a vector of Shape pointers
     * 
     */
    void PrintShapeVector(const alpha::vector<Shape*> &shapes);

    /**
     * @brief This function takes in a vector of Shape pointers and prints
     *        some of their primitive data type properties.
     * 
     * @param shapes - a string formatted in json
     * 
     * @return a vector of Shape pointers all pointing to instantiated Shapes
     * 
     */
    alpha::vector<Shape*> JsonToShapes(const std::string& json);

private:
    /**
     * @details This object works as an accumulator. As ParseJsonObject() works
     * through an object, it stores the values it finds into this accumulator. 
     * This is done because the parser is built so that the key - value pairs
     * can be "jumbled" around within an object but this parser will still work correctly
     * in spite of that. Furthermore, when the values are stored in this object,
     * they are not stored as strings, but instead, the true data type they are referring to.
     * This process is accomplished by @see UpdateMorphicShape(). This object is defined
     * in the private section so it cannot be instantiated outside this class.
     */
    struct MorphicShape {
        std::string shapeType = "";
        int shapeId = -1;
        int trackerId = -1;
        alpha::vector<int> shapeDimensions;
        QPen pen = QPen();
        QBrush brush = QBrush();
        QPoint coords = QPoint();

        QString textString;
        GlobalColor textColor;
        QFont font;
        AlignmentFlag textAlignment;
    };

    /**
     * @brief Parses a single object in the Json 
     * 
     * @details A single object is all of the data between a single {} block 
     * in the json string. This function parses just one of those objects and 
     * returns a MorphicShape. A MorphicShape object just serves as the placeholder 
     * to gather values as the object is parsed. The MorphicShape is then used to
     * instantiate an actual Shape object in JsonToShapes.
     * 
     * @param json - a string formatted in json
     * 
     * @param index - the index the parser is currently at in the json string
     * 
     * @return a MorphicShape object holding all of the data from the parsed json object
     * 
     */
    MorphicShape ParseJsonObject(const std::string json, size_t &index);

    /**
     * @brief Extracts a "key" from the json as a string
     * 
     * @details A "key" is isolated from the json string and "extracted" and returned
     *          as a string. The extracted key has no special characters (e.g. " , :)
     *          A key is a string surrounded by "" and is right before the colon
     * 
     * @param json - a string formatted in json
     * 
     * @param index - the index the parser is currently at in the json string
     * 
     * @return the "key" is returned as a string
     * 
     */
    std::string ExtractKey(const std::string& json, size_t &index);

    /**
     * @brief Extracts a "value" from the json as a string
     * 
     * @details A "value" is isolated from the json string and "extracted" and returned
     *          as a string. A value is anything right after the : and before the , or ]. 
     *          The following values are extracted: 
     *              - a string like the ShapeType or BrushColor
     *              - an integer by itself like from ShapeId
     *              - a null value from TrackerId keys
     *              - an array for ShapeDimension keys, it is extracted with brackets
     * 
     * @param json - a string formatted in json
     * 
     * @param index - the index the parser is currently at in the json string
     * 
     * @return the "value" is returned as a string
     * 
     */
    std::string ExtractValue(const std::string& json, size_t &index);

    /**
     * @brief Extracts an Integer from the value portion of json
     * 
     * @details Called by ExtractValue() when the value is found to be an integer.
     *          No special characters are included.
     * 
     * @param json - a string formatted in json
     * 
     * @param index - the index the parser is currently at in the json string
     * 
     * @return the integer is as a string
     * 
     */
    std::string ExtractInteger(const std::string& json, size_t &index);

    /**
     * @brief Extracts an Array from the value portion of json
     * 
     * @details Called by ExtractValue() when the value is found to be an Array.
     *          The extracted array is enclosed in [] and the values separated by
     *          commas.
     * 
     * @param json - a string formatted in json
     * 
     * @param index - the index the parser is currently at in the json string
     * 
     * @return the array as a string
     * 
     */
    std::string ExtractArray(const std::string& json, size_t &index);

    /**
     * @brief Extracts an null from the value portion of json
     * 
     * @details Called by ExtractValue() when the value is found to be null.
     *          No special characters are included.
     * 
     * @param json - a string formatted in json
     * 
     * @param index - the index the parser is currently at in the json string
     * 
     * @return the null as a string
     * 
     */
    std::string ExtractNull(const std::string& json, size_t &index);

    /**
     * @brief Forwards the index to the next non whitespace value
     * 
     * @details If the index is currently at a whitespace value, the index is 
     *          moved forward until a non whitespace value is encountered. If the current
     *          index is already not a whitespace, the index is returned as is.
     * 
     * @param json - a string formatted in json
     * 
     * @param index - the index the parser is currently at in the json string
     * 
     */
    void SkipWhitespace(const std::string& json, size_t& index);

    /**
     * @brief Stores the extracted value as its proper data type into a MorphicShape object
     * 
     * @details The key is used to decide which data member the value will be stored in inside
     *          MorphicShape object. Before the value is stored, it is converted from a string
     *          to its actual data type. (e.g. if the value is 1 as a string, it is stored as
     *          an integer into the MorphicShape object; if the value is green brush color, it
     *          it changes the QBrush data member object's color value to green; etc.)
     * 
     * @param key - the key extracted from the json as a string value
     * 
     * @param value - the key's corresponding value as a string
     * 
     * @param tempShape - a MorphicShape object where the value will be stored when it is converted
     *                    to its true data type
     * 
     */
    void UpdateMorphicShape(const std::string &key, const std::string &value, MorphicShape &tempShape);

    /**
     * @brief Converts an array that is currently a string value into an actual 
     *        vector of integers
     * 
     * @details Takes in a string like "[20, 32, 41, 64]" and converts it into a vector
     *          of integers with the same values.
     * 
     * @param value - the array that is currently a string
     * 
     * @return a vector of integers that can be used in C++
     * 
     */
    alpha::vector<int> StringToVector(const std::string &value);

    /**
     * @brief Takes the data from a MorphicShape and instantiates it into a true
     *        shape object, based on the data stored within it. Returns a pointer
     *        to the new shape object
     * 
     * @param tempShape - a MorphicShape object that holds all of the data that is
     *        waiting to be converted into a true Shape object.
     * 
     * @return a pointer to the newly instantiated shape object is returned
     * 
     */
    Shape* BuildShape(MorphicShape tempShape);
};

#endif // PARSER_H