/**
 * @file vector_memory_leak_test.cpp
 * @brief Driver for stress-testing alpha::vector for memory leaks under Valgrind.
 *
 * This program runs large-scale, repeated operations on our custom alpha::vector
 * class to surface any hidden memory issues. It should be run under Valgrind
 * separately from the Qt application.
 */

#include "../src/objects/vector.h"
#include <iostream>
#include <utility>
#include <cstdlib>
#include <ctime>

/**
 * @brief Main entry point for vector leak stress tests.
 *
 * Runs a series of intensive tests on alpha::vector:
 *   - push_back and operator[] over 10,000 elements
 *   - reserve and capacity check
 *   - randomized insert and erase operations
 *   - resize growth and shrink in steps
 *   - copy constructor and copy assignment
 *   - move constructor and move assignment
 *
 * Designed to be executed under Valgrind to catch any memory leaks or corruption.
 */
int main() {
    const size_t TEST_N = 10000;
    bool overallPassed = true;
    std::srand(0);

    // Test push_back and operator[]
    {
        alpha::vector<int> vec;
        for (size_t i = 0; i < TEST_N; ++i) {
            vec.push_back(static_cast<int>(i));
        }
        bool passed = (vec.size() == TEST_N);
        for (size_t i = 0; i < TEST_N && passed; ++i) {
            if (vec[i] != static_cast<int>(i)) {
                passed = false;
            }
        }
        std::cout << "push_back/operator[] test: " << (passed ? "PASSED" : "FAILED") << std::endl;
        if (!passed) {
            overallPassed = false;
        }
    }

    // Test reserve and capacity
    {
        alpha::vector<int> vec;
        vec.reserve(TEST_N);
        bool passed = (vec.capacity() >= TEST_N);
        std::cout << "reserve/capacity test: " << (passed ? "PASSED" : "FAILED") << std::endl;
        if (!passed) {
            overallPassed = false;
        }
    }

    // Test insert and erase
    {
        alpha::vector<int> vec;
        for (int i = 0; i < static_cast<int>(TEST_N); ++i) {
            vec.push_back(i);
        }
        bool passed = (vec.size() == TEST_N);
        for (int iter = 0; iter < 1000 && passed; ++iter) {
            size_t pos = std::rand() % vec.size();
            int val = -iter;
            auto it = vec.insert(vec.begin() + pos, val);
            if (*it != val) {
                passed = false;
                break;
            }
            it = vec.erase(it);
            if (vec.size() != TEST_N) {
                passed = false;
                break;
            }
        }
        std::cout << "insert/erase test: " << (passed ? "PASSED" : "FAILED") << std::endl;
        if (!passed) {
            overallPassed = false;
        }
    }

    // Test resize (grow and shrink)
    {
        alpha::vector<int> vec;
        bool passed = true;
        for (size_t sz = 0; sz <= TEST_N; sz += 1000) {
            vec.resize(sz);
            if (vec.size() != sz || vec.capacity() < sz) {
                passed = false;
            }
        }
        std::cout << "resize test: " << (passed ? "PASSED" : "FAILED") << std::endl;
        if (!passed) {
            overallPassed = false;
        }
    }

    // Test copy constructor and copy assignment
    {
        alpha::vector<int> src;
        for (size_t i = 0; i < TEST_N; ++i) {
            src.push_back(static_cast<int>(i * 2));
        }
        alpha::vector<int> copyCtor(src);
        bool passed = (copyCtor.size() == src.size() && copyCtor[TEST_N - 1] == src[TEST_N - 1]);

        alpha::vector<int> copyAssign;
        copyAssign = src;
        if (!(copyAssign.size() == src.size() && copyAssign[0] == src[0])) {
            passed = false;
        }

        std::cout << "copy constructor/assign test: " << (passed ? "PASSED" : "FAILED") << std::endl;
        if (!passed) {
            overallPassed = false;
        }
    }

    // Test move constructor and move assignment
    {
        alpha::vector<int> src;
        for (size_t i = 0; i < TEST_N; ++i) {
            src.push_back(static_cast<int>(i * 3));
        }
        alpha::vector<int> moveCtor(std::move(src));
        bool passed = (moveCtor.size() == TEST_N);

        alpha::vector<int> moveAssign;
        moveAssign = std::move(moveCtor);
        if (moveAssign.size() != TEST_N) {
            passed = false;
        }

        std::cout << "move constructor/assign test: " << (passed ? "PASSED" : "FAILED") << std::endl;
        if (!passed) {
            overallPassed = false;
        }
    }

    std::cout << "All tests completed. Overall result: "
              << (overallPassed ? "PASSED" : "FAILED") << std::endl;
    return overallPassed ? 0 : 1;
}