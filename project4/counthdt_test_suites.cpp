// counthdt_test_suites.cpp
// Glenn G. Chappell
// 27 Sep 2018
//
// For CS 311 Fall 2018
// Tests for function countHDT: test suites
// For Project 4, Exercise A
// Uses the "Catch" unit-testing framework, version 2
// Requires counthdt_test_main.cpp, catch.hpp, counthdt.h, counthdt.cpp

// Includes for code to be tested
#include "counthdt.h"       // For function countHDT
#include "counthdt.h"       // Double inclusion test

#define CATCH_CONFIG_FAST_COMPILE
                           // Disable some features for faster compile
#include "catch.hpp"       // For the "Catch" unit-testing framework

// Additional includes for this test program
#include <vector>
using std::vector;


// *********************************************************************
// Helper Functions/Classes for This Test Program
// *********************************************************************


// class TypeCheck
// This class exists in order to have static member function "check",
// which takes a parameter of a given type, by reference. Objects of
// type TypeCheck<T> cannot be created.
// Usage:
//     TypeCheck<MyType>::check(x)
//      returns true if the type of x is (MyType) or (const MyType),
//      otherwise false.
// Invariants: None.
// Requirements on Types: None.
template<typename T>
class TypeCheck {

private:

    // No default ctor
    TypeCheck() = delete;

    // Uncopyable. Do not define copy/move ctor/assn.
    TypeCheck(const TypeCheck &) = delete;
    TypeCheck(TypeCheck &&) = delete;
    TypeCheck<T> & operator=(const TypeCheck &) = delete;
    TypeCheck<T> & operator=(TypeCheck &&) = delete;

    // Compiler-generated dctor is used (but irrelevant).
    ~TypeCheck() = default;

public:

    // check
    // The function and function template below simulate a single
    // function that takes a single parameter, and returns true iff the
    // parameter has type T or (const T).

    // check (reference-to-const T)
    // Pre: None.
    // Post:
    //     Return is true.
    // Does not throw (No-Throw Guarantee)
    static bool check(const T & param)
    {
        (void)param;  // Avoid unused-parameter warning
        return true;
    }

    // check (reference-to-const non-T)
    // Pre: None.
    // Post:
    //     Return is false.
    // Requirements on types: None.
    // Does not throw (No-Throw Guarantee)
    template <typename OtherType>
    static bool check(const OtherType & param)
    {
        (void)param;  // Avoid unused-parameter warning
        return false;
    }

};  // End class TypeCheck


// check_countHDT_singletest
// Given arguments for countHDT and the expected return value (answer)
// does appropriate Catch macros INFO and REQUIRE to test whether
// countHDT returns the expected value when passed these arguments.
// Used by check_countHDT.
void check_countHDT_singletest(int w, int h,
                               int f1x, int f1y,
                               int f2x, int f2y,
                               int answer)
{
    INFO( "countHDT(" << w << "," << h << ","
           << f1x << "," << f1y << ","
           << f2x << "," << f2y <<") should return "
           << answer );
    REQUIRE( countHDT(w,h,f1x,f1y,f2x,f2y) == answer );
}


// check_countHDT
// Given vector<vector<int>>, each of whose items has size 7. Of these
// 7 values, the first 6 form valid arguments for countHDT, and the 7th
// is the expected return value.
//
// The 4 possible tests of countHDT using these values are done, using
// check_countHDT_singletest:
// - As given
// - Holes swapped
// - x, y swapped
// - Holes swapped and x,y swapped
//
// Pre:
//    For each item x of data: x.size() == 7
void check_countHDT(const vector<vector<int>> & data)
{
    for (const auto & test : data)
    {
        int w      = test[0];
        int h      = test[1];
        int f1x    = test[2];
        int f1y    = test[3];
        int f2x    = test[4];
        int f2y    = test[5];
        int answer = test[6];
        check_countHDT_singletest(w,h, f1x,f1y, f2x,f2y, answer);
        check_countHDT_singletest(w,h, f2x,f2y, f1x,f1y, answer);
        check_countHDT_singletest(h,w, f1y,f1x, f2y,f2x, answer);
        check_countHDT_singletest(h,w, f2y,f2x, f1y,f1x, answer);
    }
}


// *********************************************************************
// Test Cases
// *********************************************************************


TEST_CASE( "Function return types are correct",
           "[types]" )
{
    SECTION( "countHDT returns int by value" )
    {
        int && ii(countHDT(1, 2, 0, 0, 0, 1));
        (void)ii;  // Avoid unused-variable warnings
        INFO( "countHDT must return int by value" );
        REQUIRE( TypeCheck<int>::check(countHDT(1, 2, 0, 0, 0, 1)) );
    }
}


TEST_CASE( "1 x n boards",
           "[counting]" )
{
    SECTION( "w == 1, h < 10" )
    {
        // Test data: w, h, f1x, f1y, f2x, f2y, answer
        vector<vector<int>> data {
            {    1,   2,  0,  0,  0,  1,    1 },
            {    1,   3,  0,  0,  0,  1,    0 },
            {    1,   3,  0,  0,  0,  2,    0 },
            {    1,   3,  0,  1,  0,  2,    0 },
            {    1,   4,  0,  0,  0,  1,    1 },
            {    1,   4,  0,  0,  0,  2,    0 },
            {    1,   4,  0,  0,  0,  3,    1 },
            {    1,   4,  0,  1,  0,  2,    0 },
            {    1,   4,  0,  1,  0,  3,    0 },
            {    1,   4,  0,  2,  0,  3,    1 },
            {    1,   5,  0,  0,  0,  4,    0 },
            {    1,   6,  0,  0,  0,  1,    1 },
            {    1,   6,  0,  0,  0,  3,    1 },
            {    1,   6,  0,  0,  0,  4,    0 },
            {    1,   6,  0,  0,  0,  5,    1 },
            {    1,   6,  0,  2,  0,  5,    1 },
            {    1,   6,  0,  3,  0,  5,    0 },
            {    1,   6,  0,  4,  0,  5,    1 },
        };

        check_countHDT(data);
    }

    SECTION( "w == 1, 10 <= h <= 1000" )
    {
        // Test data: w, h, f1x, f1y, f2x, f2y, answer
        vector<vector<int>> data {
            {    1, 100,  0,  0,  0,  1,    1 },
            {    1, 100,  0,  0,  0, 49,    1 },
            {    1, 100,  0,  0,  0, 50,    0 },
            {    1, 100,  0,  0,  0, 99,    1 },
            {    1, 100,  0,  1,  0, 99,    0 },
            {    1, 100,  0, 31,  0, 99,    0 },
            {    1, 101,  0,  0,  0,  1,    0 },
            {    1, 101,  0,  0,  0,100,    0 },
            {    1, 999,  0,  0,  0,  1,    0 },
            {    1,1000,  0,  0,  0,  1,    1 },
            {    1,1000,  0,  0,  0,530,    0 },
            {    1,1000,  0,  0,  0,531,    1 },
            {    1,1000,  0, 36,  0,927,    1 },
            {    1,1000,  0, 37,  0,928,    0 },
            {    1,1000,  0, 37,  0,927,    0 },
        };

        check_countHDT(data);
    }
}

TEST_CASE( "2 x n boards",
           "[counting]" )
{
    SECTION( "w == 2, 1 <= h <= 20, holes (0,0), (1,0)" )
    {
        // Test data: w, h, f1x, f1y, f2x, f2y, answer
        vector<vector<int>> data {
            {    2,   1,  0,  0,  1,  0,    1 },
            {    2,   2,  0,  0,  1,  0,    1 },
            {    2,   3,  0,  0,  1,  0,    2 },
            {    2,   4,  0,  0,  1,  0,    3 },
            {    2,   5,  0,  0,  1,  0,    5 },
            {    2,   6,  0,  0,  1,  0,    8 },
            {    2,   7,  0,  0,  1,  0,   13 },
            {    2,   8,  0,  0,  1,  0,   21 },
            {    2,   9,  0,  0,  1,  0,   34 },
            {    2,  10,  0,  0,  1,  0,   55 },
            {    2,  11,  0,  0,  1,  0,   89 },
            {    2,  12,  0,  0,  1,  0,  144 },
            {    2,  13,  0,  0,  1,  0,  233 },
            {    2,  14,  0,  0,  1,  0,  377 },
            {    2,  15,  0,  0,  1,  0,  610 },
            {    2,  17,  0,  0,  1,  0, 1597 },
            {    2,  18,  0,  0,  1,  0, 2584 },
            {    2,  19,  0,  0,  1,  0, 4181 },
            {    2,  20,  0,  0,  1,  0, 6765 },
        };

        check_countHDT(data);
    }

    SECTION( "w == 2, 1 <= h <= 20, other holes" )
    {
        // Test data: w, h, f1x, f1y, f2x, f2y, answer
        vector<vector<int>> data {
            {    2,   2,  0,  1,  1,  0,    0 },
            {    2,   2,  1,  0,  1,  1,    1 },
            {    2,   3,  0,  0,  1,  2,    1 },
            {    2,   4,  0,  0,  0,  1,    2 },
            {    2,   5,  0,  0,  0,  1,    3 },
            {    2,   6,  0,  2,  1,  2,    6 },
            {    2,   7,  0,  3,  1,  3,    9 },
            {    2,  19,  0,  4,  1,  5,    0 },
            {    2,  20,  0,  6,  1,  6, 4901 },
        };

        check_countHDT(data);
    }
}

TEST_CASE( "Larger boards",
           "[counting]" )
{
    SECTION( "w & h both odd" )
    {
        // Test data: w, h, f1x, f1y, f2x, f2y, answer
        vector<vector<int>> data {
            {    3,   3,  0,  1,  0,  2,    0 },
            {    3,   5,  0,  1,  0,  2,    0 },
            {    3,  11,  0,  1,  0,  2,    0 },
            {    3,  13,  0,  1,  0,  2,    0 },
            {    5,   7,  0,  1,  0,  2,    0 },
        };

        check_countHDT(data);
    }

    SECTION( "Either w or h even, but still no tiling" )
    {
        // Test data: w, h, f1x, f1y, f2x, f2y, answer
        vector<vector<int>> data {
            {    3,   4,  1,  1,  2,  2,    0 },
            {    4,   5,  0,  0,  2,  2,    0 },
            {    4,   6,  1,  3,  2,  0,    0 },
            {    5,   8,  1,  5,  4,  2,    0 },
            {    6,   7,  1,  4,  3,  2,    0 },
            {    6,   7,  0,  0,  0,  2,    0 },
            {    6,   7,  0,  0,  1,  1,    0 },
        };

        check_countHDT(data);
    }
    SECTION( "Larger boards with tilings" )
    {
        // Test data: w, h, f1x, f1y, f2x, f2y, answer
        vector<vector<int>> data {
            {    3,   4,  1,  1,  2,  3,    3 },
            {    4,   5,  0,  0,  2,  3,   15 },
            {    4,   6,  1,  3,  2,  1,   29 },
            {    5,   8,  1,  5,  4,  3, 1080 },
            {    6,   7,  1,  4,  3,  3, 3312 },
            {    6,   7,  0,  0,  0,  1,14603 },
            {    6,   7,  0,  0,  1,  0,16926 },
        };

        check_countHDT(data);
    }
}

