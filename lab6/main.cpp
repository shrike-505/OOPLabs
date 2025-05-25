#include <iostream>
#include <stdexcept>
#include <string>
#include "vector.hpp"

/**
 * Prints test result to stdout
 * @param testName name of the test
 * @param passed true if the test passed, false otherwise
 */
void printTestResult(const char* testName, bool passed) {
    std::cout << "[TEST] " << testName << ": " << (passed ? "PASSED" : "FAILED") << "\n";
}

/**
 * Tests the constructors and size-related functions of the Vector class.
 * This function checks:
 * 1. The default constructor, ensuring it creates an empty Vector.
 * 2. The constructor with size parameter, verifying the Vector's size and non-empty state.
 * 3. The copy constructor, ensuring it creates a Vector with the same size and element values as the original.
 */

void testConstructorsAndSize() {
    Vector<int> v1;
    bool passed = (v1.size() == 0) && v1.empty();
    printTestResult("Default constructor", passed);

    Vector<int> v2(5);
    passed = (v2.size() == 5) && !v2.empty();
    printTestResult("Size constructor", passed);

    v2[3] = 42;
    Vector<int> v3(v2);
    passed = (v3.size() == v2.size()) && (v3[3] == 42);
    printTestResult("Copy constructor", passed);
}

/**
 * Tests the element access functions of the Vector class.
 * This function checks:
 * 1. Operator[] access, ensuring the elements are accessible and have the correct values.
 * 2. The at() function with bounds checking, verifying it throws an exception when attempting to access out-of-bounds elements.
 */
void testElementAccess() {
    Vector<int> v(3);
    for(int i = 0; i < 3; i++) v[i] = i*10;

    bool passed = true;
    passed &= (v[0] == 0);
    passed &= (v[1] == 10);
    passed &= (v[2] == 20);
    printTestResult("Operator[] access", passed);

    passed = true;
    try {
        passed &= (v.at(0) == 0);
        passed &= (v.at(2) == 20);
        v.at(3);
        passed = false;
    } catch(const std::out_of_range& e) {
    }
    printTestResult("at() with bounds checking", passed);
}

/**
 * Tests the push_back() and inflate() functions of the Vector class.
 * This function checks that each call to push_back() increases the size of the Vector by one,
 * and that the newly added element is accessible at the end of the Vector.
 */
void testPushBackAndInflate() {
    Vector<int> v;
    bool passed = true;

    for(int i = 0; i < 10; i++) {
        v.push_back(i);
        passed &= (v.size() == i+1);
    }

    passed &= (v[9] == 9);
    printTestResult("push_back and inflate", passed);
}


/**
 * Tests the clear() and empty() functions of the Vector class.
 * This function checks that a Vector clears its elements and returns
 * to an empty state.
 */
void testClearAndEmpty() {
    Vector<int> v(5);
    v.clear();
    bool passed = v.empty() && (v.size() == 0);
    printTestResult("clear and empty", passed);
}


/**
 * Tests the Vector class's exception handling.
 * This function checks that the at() function throws
 * an out_of_range exception when attempting to access
 * an element outside the Vector's bounds, either when
 * the Vector is empty (i.e. size() == 0) or when the
 * index is negative.
 */
void testExceptions() {
    Vector<int> v;
    bool passed = false;

    try {
        v.at(0);
    } catch(const std::out_of_range& e) {
        passed = true;
    }
    printTestResult("out_of_range exception (empty)", passed);

    Vector<int> v2(3);
    passed = false;
    try {
        v2.at(-1);
    } catch(const std::out_of_range& e) {
        passed = true;
    }
    printTestResult("out_of_range exception (negative)", passed);
}


/**
 * Tests the Vector class with std::string type.
 * This function checks that the Vector class can store
 * and retrieve strings, and that the size() and at()
 * functions work correctly.
 */
void testWithStrings() {
    Vector<std::string> v;
    bool passed = true;

    v.push_back("Hello");
    v.push_back("World");
    passed &= (v.size() == 2);
    passed &= (v[0] == "Hello");
    passed &= (v.at(1) == "World");

    printTestResult("string type handling", passed);
}

int main() {
    std::cout << "=== Starting Vector Tests ===\n";
    
    testConstructorsAndSize();
    testElementAccess();
    testPushBackAndInflate();
    testClearAndEmpty();
    testExceptions();
    testWithStrings();

    std::cout << "=== Tests Complete ===\n";
    return 0;
}