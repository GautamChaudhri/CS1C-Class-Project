#include "RenderAreaManager.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <QPoint>
#include <QPen>
#include <QBrush>

// Forward declarations for report-sorting routines implemented in SelSort.cpp
namespace SelSort {
    alpha::vector<Shape*> listById(const alpha::vector<Shape*>*, bool);
    alpha::vector<Shape*> listByArea(const alpha::vector<Shape*>*, bool);
    alpha::vector<Shape*> listByPerimeter(const alpha::vector<Shape*>*, bool);
}

/**
 * @brief Searches for a shape by its tracker ID in a vector of shapes.
 * @param shapes_ptr Pointer to the vector of Shape pointers to search.
 * @param trackerId The ID of the shape to find.
 * @return True if a shape with the given trackerId is found, false otherwise.
 */
bool findShape(const alpha::vector<Shape*>& shapes, int trackerId) {
    bool shapeFound = false;

    for (size_t i = 0; i < shapes.size() && !shapeFound; ++i) {
        if (trackerId == shapes[i]->getTrackerId())
            shapeFound = true;
    }
    return shapeFound;
}

/**
 * @brief Performs the first listing report white-box test.
 */
void runShapeIdReport() {
    RenderAreaManager manager(nullptr);
    manager.loadHardcodedShapes();
    alpha::vector<Shape*>* pShapes = manager.getShapesRef();

    // Pretty title and header for results
    std::cout << std::string(60, '=') << "\n";
    std::cout << std::setw(20) << "" << "White Box Test: Shape Listing Report" << "\n";
    std::cout << std::string(60, '=') << "\n\n";

    //Print initial shapes
    std::cout << "Unsorted Shapes Pre-Testing (ID Report):\n";
    std::cout << std::string(60, '-') << "\n";
    std::cout << manager.getShapesJson(*pShapes) << "\n";

    std::cout << std::left << std::setw(50) << "Test Description" << std::setw(6) << "Result" << "\n";
    std::cout << std::string(60, '-') << "\n";

    // Pre-condition: load shapes and verify if they exist
    bool shapesExist = false;
    if ((*pShapes).size() != 0) 
        shapesExist = true;
    
    std::cout << std::left << std::setw(50) << "Pre-condition: shapes imported successfully" 
                << std::setw(6) << (shapesExist ? "PASS" : "FAIL") << "\n";

    // Delete a shape
    const int deleteId = 1534;
    manager.deleteShape(deleteId);
    bool deleteSuccess = !findShape(*pShapes, deleteId);
    std::cout << std::left << std::setw(50) << "Delete shape TrackerId=" + std::to_string(deleteId)
                << std::setw(6) << (deleteSuccess ? "PASS" : "FAIL") << "\n";

    // Add a new Ellipse
    const int newEllipseId = 6281; // New unique ID for the ellipse
    Ellipse* addedEllipse = new Ellipse("Ellipse", QPoint(70, 70), QPen(Qt::green), QBrush(Qt::NoBrush), 30, 20); // Example parameters
    addedEllipse->setTrackerId(newEllipseId);
    manager.addShape(addedEllipse);
    bool addEllipseSuccess = findShape(*pShapes, newEllipseId);
    std::cout << std::left << std::setw(50) << "Add new Ellipse TrackerId=" + std::to_string(newEllipseId)
                << std::setw(6) << (addEllipseSuccess ? "PASS" : "FAIL") << "\n";

    // Modify a Circle's radius
    int circleId = 7104;
    for (Shape* shape : *pShapes) {                         //change the shape
        if (shape->getTrackerId() == circleId) {
            manager.modifyShape(shape, "Radius:", 20);
            break;
        }
    }
    bool modSuccess = false;
    for (Shape* shape : *pShapes) {                         //verify change
        if (shape->getTrackerId() == circleId) {
            Circle* circle = static_cast<Circle*>(shape);
            if (circle->getR() == 20) {
                modSuccess = true;
                break;
            }
        }
    }
    std::cout << std::left << std::setw(50) << "Modify Circle radius to 20"
                << std::setw(6) << (modSuccess ? "PASS" : "FAIL") << "\n";

    // Modify a Square's length
    const int squareId = 5890;
    int newSide = 80;
    for (Shape* shape : *pShapes) {                         //change the shape
        if (shape->getTrackerId() == squareId) {
            manager.modifyShape(shape, "Length:", newSide); // Assuming "Length" is the correct key for Square's side
            break;
        }
    }
    bool squarePass = false;
    for (Shape* shape : *pShapes) {                         //verify change
        if (shape->getTrackerId() == squareId) {
            Square* square = static_cast<Square*>(shape);
            if (square->getLength() == newSide) { // Assuming getLength() is the correct getter for Square's side
                squarePass = true;
                break;
            }
        }
    }
    std::cout << std::left << std::setw(50) << "Modify Square Side=" + std::to_string(newSide)
              << std::setw(6) << (squarePass ? "PASS" : "FAIL") << "\n";

    // Modify a Rectangle's length and width
    const int rectId = 4098;
    int newLength = 50, newWidth = 75;
    for (Shape* shape : *pShapes) {                         //change the shape
        if (shape->getTrackerId() == rectId) {
            manager.modifyShape(shape, "Length:", newLength);
            manager.modifyShape(shape, "Width:", newWidth);
            break;
        }
    }
    bool rectPass = false;
    for (Shape* shape : *pShapes) {                         //verify change
        if (shape->getTrackerId() == rectId) {
            Rectangle* rect = static_cast<Rectangle*>(shape);
            if (rect->getLength() == newLength && rect->getWidth() == newWidth) {
                rectPass = true;
                break;
            }
        }
    }
    std::cout << std::left << std::setw(50) << "Modify Rectangle L=" + std::to_string(newLength) + ", W=" + std::to_string(newWidth)
              << std::setw(6) << (rectPass ? "PASS" : "FAIL") << "\n";
    std::cout << std::string(60, '-') << "\n\n";

    // Final sorted report
    auto sortedShapes = SelSort::listById(pShapes, true);
    std::cout << "Sorted Shapes Post-Testing (ID Report):\n";
    std::cout << std::string(60, '-') << "\n";
    std::cout << manager.getShapesJson(sortedShapes) << "\n";
}

/**
 * @brief Performs the second listing report: prints each shape's dimensions and area,
 *        then outputs a perimeter-sorted JSON of shapes.
 */
void runShapeAreaReport() {
    RenderAreaManager manager(nullptr);
    manager.loadHardcodedShapes();
    alpha::vector<Shape*>* pShapes = manager.getShapesRef();

    // Pretty title and header for results
    std::cout << std::string(60, '=') << "\n";
    std::cout << std::setw(20) << "" << "White Box Test: Shape Area Report" << "\n";
    std::cout << std::string(60, '=') << "\n\n";

    // Print initial shapes JSON
    std::cout << "Unsorted Shapes Pre-Testing (Area Report):\n";
    std::cout << std::string(60, '-') << "\n";
    std::cout << manager.getShapesJson(*pShapes) << "\n\n";

    // Sort shapes now so report matches sorted json order
    auto intermediary = SelSort::listByArea(pShapes, true);
    pShapes = &intermediary;

    // Test description: shape type, dimensions, and calculated area
    std::cout << std::left
              << std::setw(15) << "Shape Report"
              << std::setw(12) << "Tracker ID"
              << std::setw(20) << "Dimensions"
              << std::setw(10) << "Area" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (Shape* shape : *pShapes) {
        std::string type = shape->getShapeType();
        std::cout << std::left
                  << std::setw(18) << type
                  << std::setw(9) << shape->getTrackerId();
        
        if (type == "Square") {
            Square* sq = static_cast<Square*>(shape);
            std::string dims = "Side=" + std::to_string(sq->getLength());
            double area = shape->Area();
            std::cout << std::setw(20) << dims
                      << std::setw(10) << area << "\n";
        } else if (type == "Rectangle") {
            Rectangle* rect = static_cast<Rectangle*>(shape);
            std::string dims = "L=" + std::to_string(rect->getLength()) +
                               ", W=" + std::to_string(rect->getWidth());
            double area = shape->Area();
            std::cout << std::setw(20) << dims
                      << std::setw(10) << area << "\n";
        } else if (type == "Circle") {
            Circle* cir = static_cast<Circle*>(shape);
            std::string dims = "R=" + std::to_string(cir->getR());
            double area = shape->Area();
            std::cout << std::setw(20) << dims
                      << std::setw(10) << area << "\n";
        } else {
            double area = shape->Area();
            std::cout << std::setw(20) << "N/A"
                      << std::setw(10) << ((area == 0) ? "N/A" : std::to_string(area)) << "\n";
        }
    }
    std::cout << std::string(60, '-') << "\n";


    // Apply modifications to specific shapes
    std::cout << "\nApplying modifications to shapes:\n";
    std::cout << std::string(60, '-') << "\n";
    for (Shape* shape : *pShapes) {
        std::string type = shape->getShapeType();
        if (type == "Square") {
            manager.modifyShape(shape, "Length:", 240);
            std::cout << "Modified Square (ID=" << shape->getTrackerId() 
                      << ") side to 240\n";
        } else if (type == "Rectangle") {
            manager.modifyShape(shape, "Length:", 165);
            std::cout << "Modified Rectangle (ID=" << shape->getTrackerId() 
                      << ") length to 165\n";
        } else if (type == "Circle") {
            manager.modifyShape(shape, "Radius:", 35);
            std::cout << "Modified Circle (ID=" << shape->getTrackerId() 
                      << ") radius to 35\n";
        }
    }
    std::cout << std::string(60, '-') << "\n\n";

    // Sort shapes now so report matches sorted json order
    intermediary = SelSort::listByArea(pShapes, true);
    pShapes = &intermediary;

    // Test description: shape type, dimensions, and calculated area
    std::cout << std::left
              << std::setw(15) << "Shape Report"
              << std::setw(12) << "Tracker ID"
              << std::setw(20) << "Dimensions"
              << std::setw(10) << "Area" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (Shape* shape : *pShapes) {
        std::string type = shape->getShapeType();
        std::cout << std::left
                  << std::setw(18) << type
                  << std::setw(9) << shape->getTrackerId();
        
        if (type == "Square") {
            Square* sq = static_cast<Square*>(shape);
            std::string dims = "Side=" + std::to_string(sq->getLength());
            double area = shape->Area();
            std::cout << std::setw(20) << dims
                      << std::setw(10) << area << "\n";
        } else if (type == "Rectangle") {
            Rectangle* rect = static_cast<Rectangle*>(shape);
            std::string dims = "L=" + std::to_string(rect->getLength()) +
                               ", W=" + std::to_string(rect->getWidth());
            double area = shape->Area();
            std::cout << std::setw(20) << dims
                      << std::setw(10) << area << "\n";
        } else if (type == "Circle") {
            Circle* cir = static_cast<Circle*>(shape);
            std::string dims = "R=" + std::to_string(cir->getR());
            double area = shape->Area();
            std::cout << std::setw(20) << dims
                      << std::setw(10) << area << "\n";
        } else {
            double area = shape->Area();
            std::cout << std::setw(20) << "N/A"
                      << std::setw(10) << ((area == 0) ? "N/A" : std::to_string(area)) << "\n";
        }
    }
    std::cout << std::string(60, '-') << "\n\n";


    // Final sorted report by area
    auto sortedShapes = SelSort::listByArea(pShapes, true);
    std::cout << "Sorted Shapes Post-Testing (Area Report):\n";
    std::cout << std::string(60, '-') << "\n";
    std::cout << manager.getShapesJson(sortedShapes) << "\n";
}

/**
 * @brief Performs the third listing report: prints each shape's dimensions and perimeter,
 *        then outputs a perimeter-sorted JSON of shapes.
 */
void runShapePerimeterReport() {
    RenderAreaManager manager(nullptr);
    manager.loadHardcodedShapes();
    alpha::vector<Shape*>* pShapes = manager.getShapesRef();

    // Pretty title and header for results
    std::cout << std::string(60, '=') << "\n";
    std::cout << std::setw(20) << "" << "White Box Test: Shape Perimeter Report" << "\n";
    std::cout << std::string(60, '=') << "\n\n";

    // Print initial shapes JSON
    std::cout << "Unsorted Shapes Pre-Testing (Perimeter Report):\n";
    std::cout << std::string(60, '-') << "\n";
    std::cout << manager.getShapesJson(*pShapes) << "\n\n";

    // Sort by perimeter for initial test
    auto intermediary = SelSort::listByPerimeter(pShapes, true);
    pShapes = &intermediary;

    // Test description: shape type, tracker ID, dimensions, and calculated perimeter
    std::cout << std::left
              << std::setw(15) << "Shape Report"
              << std::setw(12) << "Tracker ID"
              << std::setw(20) << "Dimensions"
              << std::setw(10) << "Perimeter" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (Shape* shape : *pShapes) {
        std::string type = shape->getShapeType();
        std::cout << std::left
                  << std::setw(18) << type
                  << std::setw(9) << shape->getTrackerId();

        double perim = shape->Perimeter();
        if (type == "Square") {
            Square* sq = static_cast<Square*>(shape);
            std::string dims = "Side=" + std::to_string(sq->getLength());
            std::cout << std::setw(20) << dims
                      << std::setw(10)
                      << ((perim == 0) ? "N/A" : std::to_string(perim))
                      << "\n";
        } else if (type == "Rectangle") {
            Rectangle* rect = static_cast<Rectangle*>(shape);
            std::string dims = "L=" + std::to_string(rect->getLength()) +
                               ", W=" + std::to_string(rect->getWidth());
            std::cout << std::setw(20) << dims
                      << std::setw(10)
                      << ((perim == 0) ? "N/A" : std::to_string(perim))
                      << "\n";
        } else if (type == "Circle") {
            Circle* cir = static_cast<Circle*>(shape);
            std::string dims = "R=" + std::to_string(cir->getR());
            std::cout << std::setw(20) << dims
                      << std::setw(10)
                      << ((perim == 0) ? "N/A" : std::to_string(perim))
                      << "\n";
        } else {
            std::cout << std::setw(20) << "N/A"
                      << std::setw(10)
                      << ((perim == 0) ? "N/A" : std::to_string(perim))
                      << "\n";
        }
    }
    std::cout << std::string(60, '-') << "\n\n";

    // Apply modifications to specific shapes (to test post-condition)
    std::cout << "\nApplying modifications to shapes:\n";
    std::cout << std::string(60, '-') << "\n";
    for (Shape* shape : *pShapes) {
        std::string type = shape->getShapeType();
        if (type == "Square") {
            manager.modifyShape(shape, "Length:", 240);
            std::cout << "Modified Square (ID=" << shape->getTrackerId()
                      << ") side to 240\n";
        } else if (type == "Rectangle") {
            manager.modifyShape(shape, "Length:", 165);
            std::cout << "Modified Rectangle (ID=" << shape->getTrackerId()
                      << ") length to 165\n";
        } else if (type == "Circle") {
            manager.modifyShape(shape, "Radius:", 35);
            std::cout << "Modified Circle (ID=" << shape->getTrackerId()
                      << ") radius to 35\n";
        }
    }
    std::cout << std::string(60, '-') << "\n\n";

    // Re-sort by perimeter for post-test
    intermediary = SelSort::listByPerimeter(pShapes, true);
    pShapes = &intermediary;

    // Repeat report output after modifications
    std::cout << std::left
              << std::setw(15) << "Shape Report"
              << std::setw(12) << "Tracker ID"
              << std::setw(20) << "Dimensions"
              << std::setw(10) << "Perimeter" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (Shape* shape : *pShapes) {
        std::string type = shape->getShapeType();
        std::cout << std::left
                  << std::setw(18) << type
                  << std::setw(9) << shape->getTrackerId();

        double perim = shape->Perimeter();
        if (type == "Square") {
            Square* sq = static_cast<Square*>(shape);
            std::string dims = "Side=" + std::to_string(sq->getLength());
            std::cout << std::setw(20) << dims
                      << std::setw(10)
                      << ((perim == 0) ? "N/A" : std::to_string(perim))
                      << "\n";
        } else if (type == "Rectangle") {
            Rectangle* rect = static_cast<Rectangle*>(shape);
            std::string dims = "L=" + std::to_string(rect->getLength()) +
                               ", W=" + std::to_string(rect->getWidth());
            std::cout << std::setw(20) << dims
                      << std::setw(10)
                      << ((perim == 0) ? "N/A" : std::to_string(perim))
                      << "\n";
        } else if (type == "Circle") {
            Circle* cir = static_cast<Circle*>(shape);
            std::string dims = "R=" + std::to_string(cir->getR());
            std::cout << std::setw(20) << dims
                      << std::setw(10)
                      << ((perim == 0) ? "N/A" : std::to_string(perim))
                      << "\n";
        } else {
            std::cout << std::setw(20) << "N/A"
                      << std::setw(10)
                      << ((perim == 0) ? "N/A" : std::to_string(perim))
                      << "\n";
        }
    }
    std::cout << std::string(60, '-') << "\n\n";

    // Final sorted report by perimeter
    auto sortedShapes = SelSort::listByPerimeter(pShapes, true);
    std::cout << "Sorted Shapes Post-Testing (Perimeter Report):\n";
    std::cout << std::string(60, '-') << "\n";
    std::cout << manager.getShapesJson(sortedShapes) << "\n";
}

/**
 * @brief Entry point for test harness.
 */
int main() {
    runShapeIdReport();
    std::cout << std::endl << std::endl;
    runShapeAreaReport();
    std::cout << std::endl << std::endl;
    runShapePerimeterReport();
    return 0;
}