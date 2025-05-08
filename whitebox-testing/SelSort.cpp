#include <algorithm>
#include "objects/all_shapes.h"

namespace SelSort {

// Selection sort copied from MainWindow, adapted for free functions
// These functions have been refactored to function in this test harness
// for whitebox testing. However, the core logic remains exactly the same
// as the originals.
static void selection_sort(alpha::vector<Shape*>& shapes,
                           bool (*compare)(const Shape*, const Shape*),
                           bool ascending)
{
   for (size_t i = 0; i < shapes.size(); ++i) {
        size_t targetIdx = i;
        for (size_t j = i + 1; j < shapes.size(); ++j) {
            if (ascending ? compare(shapes[j], shapes[targetIdx])
                          : compare(shapes[targetIdx], shapes[j])) {
                targetIdx = j;
            }
        }
        if (targetIdx != i) {
            std::swap(shapes[i], shapes[targetIdx]);
        }
    }
}

// Compare functions, same logic as MainWindow::sortBy...
static bool compareById(const Shape* a, const Shape* b) {
    return a->getTrackerId() < b->getTrackerId();
}

static bool compareByArea(const Shape* a, const Shape* b) {
    return a->Area() < b->Area();
}

static bool compareByPerimeter(const Shape* a, const Shape* b) {
    return a->Perimeter() < b->Perimeter();
}

// Public API: return a sorted copy of the input vector
alpha::vector<Shape*> listById(const alpha::vector<Shape*>* shapes_ptr, bool ascending) {
    if (!shapes_ptr) return alpha::vector<Shape*>(); // Return empty if null
    auto shapesCopy = *shapes_ptr; // Dereference to copy the vector
    selection_sort(shapesCopy, compareById, ascending);
    return shapesCopy;
}

alpha::vector<Shape*> listByArea(const alpha::vector<Shape*>* shapes_ptr, bool ascending) {
    if (!shapes_ptr) return alpha::vector<Shape*>(); // Return empty if null
    auto shapesCopy = *shapes_ptr; // Dereference to copy the vector
    selection_sort(shapesCopy, compareByArea, ascending);
    return shapesCopy;
}

alpha::vector<Shape*> listByPerimeter(const alpha::vector<Shape*>* shapes_ptr, bool ascending) {
    if (!shapes_ptr) return alpha::vector<Shape*>(); // Return empty if null
    auto shapesCopy = *shapes_ptr; // Dereference to copy the vector
    selection_sort(shapesCopy, compareByPerimeter, ascending);
    return shapesCopy;
}

} // namespace SelSort