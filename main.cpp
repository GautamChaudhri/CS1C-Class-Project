//main.cpp
#include <iostream>
using namespace std;

#include <iostream>
#include "vector/vector.h"


/**********************************************************************
 * Main
 ======================================================================
 * This function
 ======================================================================
 * Pre-condition:
 *      
 * Post-condition:
 *      
**********************************************************************/
int main() {

    // TEST DEFAULT CONTSTRUCTOR
    vector<int> testVec;
    cout << "Test Size: " << testVec.size();
    cout << "\nTest Capacity: " << testVec.capacity();


    return 0;
}