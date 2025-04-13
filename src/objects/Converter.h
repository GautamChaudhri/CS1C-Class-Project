//Converter.h
#ifndef CONVERTER_H
#define CONVERTER_H
#include <iostream>
#include "shapes/all_shapes.h"
#include "vector.h"

class Converter {
public:
    alpha::vector<Shape*> parseJson(const std::string& json) {
        alpha::vector<Shape*> shapes;
        Shape* newShape = nullptr;

        size_t index = 0;
        if (json[index] != '[')
            throw std::runtime_error("Expected '[' at the beginning of string.");
        else
            index++;
        
        while (true) {
            if (json[index] == ']')
                break;
            
            alpha::vector<Shape*> shapeMap = parseObjectJson(json, index);

            newShape = BuildShape(shapeMap);
            shapes.push_back(newShape);

            if(json[index] == ',')
                index++;
            else if (json[index] == ']')
                break;
            else
                throw std::runtime_error("Expected ',' or ']'.");
        }
    }

private: 
    alpha::vector<Shape*> parseObjectJson(const std::string, size_t index) {

    }

    Shape* BuildShape(alpha::vector<Shape*> shapeMap) {
        Shape* shape = nullptr;
        //int shapeId = shapeMap[0];
    }
};

#endif //CONVERTER_H