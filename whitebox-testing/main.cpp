#include "RenderAreaManager.h"
// Forward declarations for report-sorting routines implemented in SelSort.cpp
namespace SelSort {
    alpha::vector<Shape*> listById(const alpha::vector<Shape*>&, bool);
    alpha::vector<Shape*> listByArea(const alpha::vector<Shape*>&, bool);
    alpha::vector<Shape*> listByPerimeter(const alpha::vector<Shape*>&, bool);
}
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <QPoint>
#include <QPen>
#include <QBrush>

/**
 * @brief Performs the first listing report white-box test.
 */
void runFirstListingReportTest() {
    RenderAreaManager manager;
    manager.loadHardcodedShapes();
    auto shapes = manager.getShapesVector();

    // Pretty title and header for results
    std::cout << std::string(60, '=') << "\n";
    std::cout << std::setw(20) << "" << "White Box Test: Shape Listing Report" << "\n";
    std::cout << std::string(60, '=') << "\n\n";
    std::cout << std::left << std::setw(50) << "Test Description" << std::setw(6) << "Result" << "\n";
    std::cout << std::string(56, '-') << "\n";

    // Pre-condition: verify sorted by TrackerId
    auto sortedPre = SelSort::listById(shapes, true);
    bool preOK = true;
    for (size_t i = 1; i < sortedPre.size(); ++i) {
        if (sortedPre[i-1]->getTrackerId() > sortedPre[i]->getTrackerId()) {
            preOK = false;
            break;
        }
    }
    {
        bool pass = preOK;
        std::cout << std::left << std::setw(50) << "Pre-condition: sort by TrackerId" 
                  << std::setw(6) << (pass ? "PASS" : "FAIL") << "\n";
    }

    // Post-condition 1: delete a shape
    const int deleteId = 1534;
    manager.deleteShape(deleteId);
    shapes = manager.getShapesVector();
    bool deleteOK = std::none_of(shapes.begin(), shapes.end(),
        [deleteId](Shape* s){ return s->getTrackerId() == deleteId; });
    {
        bool pass = deleteOK;
        std::cout << std::left << std::setw(50) << "Delete shape TrackerId=" + std::to_string(deleteId)
                  << std::setw(6) << (pass ? "PASS" : "FAIL") << "\n";
    }

    // Post-condition 2: add a new Circle
    const int newCircleId = 7500;
    Circle* addedCircle = new Circle("Circle", QPoint(10, 10), QPen(Qt::black), QBrush(Qt::NoBrush), 15);
    addedCircle->setTrackerId(newCircleId);
    manager.addShape(addedCircle);
    shapes = manager.getShapesVector();
    bool addOK = std::any_of(shapes.begin(), shapes.end(),
        [newCircleId](Shape* s){ return s->getTrackerId() == newCircleId; });
    {
        bool pass = addOK;
        std::cout << std::left << std::setw(50) << "Add new Circle TrackerId=" + std::to_string(newCircleId)
                  << std::setw(6) << (pass ? "PASS" : "FAIL") << "\n";
    }

    // Post-condition 3: modify a Circle's radius via modifyShape
    bool modifyCircleOK = false;
    for (auto s : shapes) {
        if (s->getTrackerId() == newCircleId) {
            manager.modifyShape(s, "Radius:", 20);
            // verify
            if (auto c = dynamic_cast<Circle*>(s)) {
                modifyCircleOK = (c->getR() == 20);
            }
            break;
        }
    }
    {
        bool pass = modifyCircleOK;
        std::cout << std::left << std::setw(50) << "Modify Circle radius to 20"
                  << std::setw(6) << (pass ? "PASS" : "FAIL") << "\n";
    }

    // Post-condition 4: modify Rectangle length/width
    const int rectId = 4098;
    int newLength = 50, newWidth = 75;
    bool rectPass = false;
    for (auto s : shapes) {
        if (s->getTrackerId() == rectId) {
            manager.modifyShape(s, "Length:", newLength);
            manager.modifyShape(s, "Width:", newWidth);
            if (auto r = dynamic_cast<Rectangle*>(s)) {
                bool lenOK = (r->getLength() == newLength);
                bool widOK = (r->getWidth() == newWidth);
                rectPass = (lenOK && widOK);
            }
            break;
        }
    }
    {
        bool pass = rectPass;
        std::cout << std::left << std::setw(50) << "Modify Rectangle TrackerId=" + std::to_string(rectId)
                  << std::setw(6) << (pass ? "PASS" : "FAIL") << "\n";
    }

    // Post-condition 5: modify Square length
    const int squareId = 5890;
    int newSide = 80;
    bool squarePass = false;
    for (auto s : shapes) {
        if (s->getTrackerId() == squareId) {
            manager.modifyShape(s, "Length:", newSide);
            if (auto sq = dynamic_cast<Square*>(s)) {
                squarePass = (sq->getLength() == newSide);
            }
            break;
        }
    }
    {
        bool pass = squarePass;
        std::cout << std::left << std::setw(50) << "Modify Square TrackerId=" + std::to_string(squareId)
                  << std::setw(6) << (pass ? "PASS" : "FAIL") << "\n";
    }

    // Final sorted report
    auto sortedPost = SelSort::listById(manager.getShapesVector(), true);
    std::cout << "\n" << std::left << std::setw(10) << "ID" 
              << std::setw(15) << "Type" << "\n";
    std::cout << std::string(25, '-') << "\n";
    for (auto s : sortedPost) {
        std::cout << std::left << std::setw(10) << s->getTrackerId()
                  << std::setw(15) << s->getShapeType() << "\n";
    }
}

/**
 * @brief Entry point for test harness.
 */
int main() {
    runFirstListingReportTest();
    return 0;
}