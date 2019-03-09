// da3_test_suites.cpp
// Glenn G. Chappell
// 23 Sep 2018
//
// For CS 311 Fall 2018
// Tests for Project 3 Functions & Templates: test suites
// For Project 3, Exercises A, B, C, D
// Uses the "Catch" unit-testing framework, version 2
// Requires da3_test_main.cpp, catch.hpp, da3.h, da3.cpp

// Includes for code to be tested
#include "da3.h"           // For Project 3 Functions & Templates
#include "da3.h"           // Double inclusion test

#define CATCH_CONFIG_FAST_COMPILE
                           // Disable some features for faster compile
#include "catch.hpp"       // For the "Catch" unit-testing framework

// Additional includes for this test program
#include <stdexcept>
using std::out_of_range;
using std::runtime_error;
#include <vector>
using std::vector;
#include <algorithm>
using std::equal;
#include <deque>
using std::deque;
#include <utility>
using std::pair;
#include <string>
using std::string;
#include <initializer_list>
using std::initializer_list;


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


// thisThrows
// Throws a std::runtime_error. For passing to function doesItThrow.
// Will throw std::runtime_error.
void thisThrows()
{
    throw std::runtime_error("Hi!");
}

// thisThrowsStrangely
// Throws an int. For passing to function doesItThrow.
// Will throw int.
void thisThrowsStrangely()
{
    throw -42;
}

// class FuncObj
// Class for do-nothing function objects.
// Do "FuncObj x;", and then we can do "x();".
// The operator() returns nothing and does not throw.
// Invariants: None.
class FuncObj {

// ***** FuncObj: ctors, dctor, op= *****
public:

    // Compiler-generated default ctor, Big 5 are used
    FuncObj() = default;
    FuncObj(const FuncObj & other) = default;
    FuncObj & operator=(const FuncObj & other) = default;
    FuncObj(FuncObj && other) = default;
    FuncObj & operator=(FuncObj && other) = default;

// ***** FuncObj: public operators *****
public:

    // operator()
    // Makes an object of this class callable like a function.
    // Does not throw.
    void operator()() const
    {}

};  // end class FuncObj


// *********************************************************************
// Test Cases
// *********************************************************************


TEST_CASE( "Function return types are correct",
           "[types]" )
{
    int throw_stat;  // 0: no throw, 1: throw, 2: throw other

    SECTION( "lookup returns value type by value" )
    {
        LLNode<int> * headi = nullptr;
        headi = new LLNode<int>(1, headi);
        try
        {
            int && ii(lookup(headi, 0));
            (void)ii;  // Avoid unused-variable warning
            throw_stat = 0;
        }
        catch (...)
        {
            throw_stat = 1;
        }

        {
        INFO( "lookup does not throw" );
        REQUIRE( throw_stat == 0 );
        }
        {
        INFO( "lookup returns int" );
        REQUIRE( TypeCheck<int>::check(lookup(headi, 0)) );
        }

        LLNode<double> * headd = nullptr;
        headd = new LLNode<double>(1.1, headd);
        try
        {
            double && dd(lookup(headd, 0));
            (void)dd;  // Avoid unused-variable warning
            throw_stat = 0;
        }
        catch (...)
        {
            throw_stat = 1;
        }

        {
        INFO( "lookup does not throw" );
        REQUIRE( throw_stat == 0 );
        }
        {
        INFO( "lookup returns double" );
        REQUIRE( TypeCheck<double>::check(lookup(headd, 0)) );
        }
    }

    SECTION( "uniqueCount returns size_t by value" )
    {
        vector<int> v { 1, 2, 3 };
        size_t && st(uniqueCount(v.begin(), v.end()));
        (void)st;  // Avoid unused-variable warning
        INFO( "uniqueCount must return std::size_t" );
        REQUIRE( TypeCheck<size_t>::check(uniqueCount(v.begin(), v.end())) );
    }

    SECTION( "modExp returns int by value" )
    {
        int && i(modExp(1,2,3));
        (void)i;  // Avoid unused-variable warning
        INFO( "modExp returns int by value" );
        REQUIRE( TypeCheck<int>::check(modExp(1,2,3)) );
    }
}


TEST_CASE( "Function template lookup",
           "[ex-a]" )
{
    int throw_stat;  // 0: no throw, 1: throw, 2: throw other
    bool nonempty_what;  // Valid only if throw_stat == 1

    LLNode<int> * headi;     // Head ptr for all int Linked Lists
    LLNode<double> * headd;  // Head ptr for all double Linked Lists

    int ival;                // int value
    double dval;             // double value

    SECTION( "Size 0" )
    {
        // Construct list
        headi = nullptr;

        // Index 0
        try
        {
            int && ii = lookup(headi, 0);
            (void)ii;  // Avoid unused-variable warning
            throw_stat = 0;
        }
        catch (out_of_range & e)
        {
            throw_stat = 1;
            nonempty_what = (string("") != e.what());
        }
        catch (...)
        {
            throw_stat = 2;
        }

        {
        INFO( "lookup must throw on out-of-range index" );
        REQUIRE( throw_stat != 0 );
        }
        {
        INFO( "lookup must throw only std::out_of_range" );
        REQUIRE( throw_stat == 1 );
        }
        {
        INFO( "lookup must throw exception with nonempty .what()" );
        REQUIRE( nonempty_what );
        }

        // Index 1
        try
        {
            int && ii = lookup(headi, 1);
            (void)ii;  // Avoid unused-variable warning
            throw_stat = 0;
        }
        catch (out_of_range & e)
        {
            throw_stat = 1;
            nonempty_what = (string("") != e.what());
        }
        catch (...)
        {
            throw_stat = 2;
        }

        {
        INFO( "lookup must throw on out-of-range index" );
        REQUIRE( throw_stat != 0 );
        }
        {
        INFO( "lookup must throw only std::out_of_range" );
        REQUIRE( throw_stat == 1 );
        }
        {
        INFO( "lookup must throw exception with nonempty .what()" );
        REQUIRE( nonempty_what );
        }
    }

    SECTION( "Size 1" )
    {
        // Construct list
        headd = nullptr;
        headd = new LLNode<double>(3.2, headd);

        // Index 0
        try
        {
            double && dd = lookup(headd, 0);
            throw_stat = 0;
            dval = dd;
        }
        catch (...)
        {
            throw_stat = 1;
        }

        {
        INFO( "lookup must not throw on in-range index" );
        REQUIRE( throw_stat == 0 );
        }
        {
        INFO( "lookup must return 3.2" );
        REQUIRE( dval == 3.2 );
        }

        // Index 1
        try
        {
            double && dd = lookup(headd, 1);
            (void)dd;  // Avoid unused-variable warning
            throw_stat = 0;
        }
        catch (out_of_range & e)
        {
            throw_stat = 1;
            nonempty_what = (string("") != e.what());
        }
        catch (...)
        {
            throw_stat = 2;
        }

        {
        INFO( "lookup must throw on out-of-range index" );
        REQUIRE( throw_stat != 0 );
        }
        {
        INFO( "lookup must throw only std::out_of_range" );
        REQUIRE( throw_stat == 1 );
        }
        {
        INFO( "lookup must throw exception with nonempty .what()" );
        REQUIRE( nonempty_what );
        }
    }

    SECTION( "Size 9" )
    {
        // Construct list
        headi = nullptr;
        headi = new LLNode<int>(64, headi);
        headi = new LLNode<int>(49, headi);
        headi = new LLNode<int>(36, headi);
        headi = new LLNode<int>(25, headi);
        headi = new LLNode<int>(16, headi);
        headi = new LLNode<int>(9, headi);
        headi = new LLNode<int>(4, headi);
        headi = new LLNode<int>(1, headi);
        headi = new LLNode<int>(0, headi);

        // Index 0
        try
        {
            int && ii = lookup(headi, 0);
            throw_stat = 0;
            ival = ii;
        }
        catch (...)
        {
            throw_stat = 1;
        }

        {
        INFO( "lookup must not throw on in-range index" );
        REQUIRE( throw_stat == 0 );
        }
        {
        INFO( "lookup must return 0" );
        REQUIRE( ival == 0 );
        }

        // Index 5
        try
        {
            int && ii = lookup(headi, 5);
            throw_stat = 0;
            ival = ii;
        }
        catch (...)
        {
            throw_stat = 1;
        }

        {
        INFO( "lookup must not throw on in-range index" );
        REQUIRE( throw_stat == 0 );
        }
        {
        INFO( "lookup must return 25" );
        REQUIRE( ival == 25 );
        }

        // Index 8
        try
        {
            int && ii = lookup(headi, 8);
            throw_stat = 0;
            ival = ii;
        }
        catch (...)
        {
            throw_stat = 1;
        }

        {
        INFO( "lookup must not throw on in-range index" );
        REQUIRE( throw_stat == 0 );
        }
        {
        INFO( "lookup must return 64" );
        REQUIRE( ival == 64 );
        }

        // Index 9
        try
        {
            int && ii = lookup(headi, 9);
            (void)ii;  // Avoid unused-variable warning
            throw_stat = 0;
        }
        catch (out_of_range & e)
        {
            throw_stat = 1;
            nonempty_what = (string("") != e.what());
        }
        catch (...)
        {
            throw_stat = 2;
        }

        {
        INFO( "lookup must throw on out-of-range index" );
        REQUIRE( throw_stat != 0 );
        }
        {
        INFO( "lookup must throw only std::out_of_range" );
        REQUIRE( throw_stat == 1 );
        }
        {
        INFO( "lookup must throw exception with nonempty .what()" );
        REQUIRE( nonempty_what );
        }

        // Index 100
        try
        {
            int && ii = lookup(headi, 100);
            (void)ii;  // Avoid unused-variable warning
            throw_stat = 0;
        }
        catch (out_of_range & e)
        {
            throw_stat = 1;
            nonempty_what = (string("") != e.what());
        }
        catch (...)
        {
            throw_stat = 2;
        }

        {
        INFO( "lookup must throw on out-of-range index" );
        REQUIRE( throw_stat != 0 );
        }
        {
        INFO( "lookup must throw only std::out_of_range" );
        REQUIRE( throw_stat == 1 );
        }
        {
        INFO( "lookup must throw exception with nonempty .what()" );
        REQUIRE( nonempty_what );
        }
    }
}


TEST_CASE( "Function template didItThrow",
           "[ex-b]" )
{
    bool didThrow;  // Whether function throws or not

    SECTION( "Function throws standard exception class" )
    {
        didThrow = false;
        try
        {
            didItThrow(thisThrows, didThrow);
            INFO( "Throwing function #1 - should re-throw same exception" );
            REQUIRE( false );
        }
        catch (std::runtime_error & e)
        {
            INFO( "Throwing function #1 - should re-throw same exception" );
            REQUIRE( std::string("Hi!") == e.what() );
        }
        catch (...)
        {
            INFO( "Throwing function #1 - should re-throw same exception" );
            REQUIRE( false );
        }
        {
        INFO( "Throwing function #1 - bool param is true" );
        REQUIRE( didThrow );
        }
    }

    SECTION( "Function throws int" )
    {
        didThrow = false;
        try
        {
            didItThrow(thisThrowsStrangely, didThrow);
            INFO( "Throwing function #2 - should re-throw same exception" );
            REQUIRE( false );
        }
        catch (int & e)
        {
            INFO( "Throwing function #2 - should re-throw same exception" );
            REQUIRE( e == -42 );
        }
        catch (...)
        {
            INFO( "Throwing function #2 - should re-throw same exception" );
            REQUIRE( false );
        }
        {
        INFO( "Throwing function #2 - bool param is true" );
        REQUIRE( didThrow );
        }
    }

    SECTION( "Function object, does not throw" )
    {
        didThrow = true;
        try
        {
            didItThrow(FuncObj(), didThrow);
            INFO( "Non-throwing function object - should not throw" );
            REQUIRE( true );
        }
        catch (...)
        {
            INFO( "Non-throwing function object - should not throw" );
            REQUIRE( false );
        }
        {
        INFO( "Non-throwing function object - bool param is false" );
        REQUIRE_FALSE( didThrow );
        }
    }
}


TEST_CASE( "Function template uniqueCount",
           "[ex-c]" )
{
    deque<int> di {                  // Test data
        1, 1, 2, 1, 2, 2, 3, -1, -1, -1, 5, 3, 3, 3, 2, 2, 1, 1, 1
    };
    const size_t bigsize = 10000;  // Size of very long ranges
                                   //  Must be > 9000

    SECTION( "Empty range" )
    {
        size_t && result = uniqueCount(di.rbegin(), di.rbegin());
        INFO( "uniqueCount must return 0" );
        REQUIRE( result == 0 );
    }

    SECTION( "Range of size 1" )
    {
        size_t && result = uniqueCount(di.rbegin()+3, di.rbegin()+4);
        INFO( "uniqueCount must return 1" );
        REQUIRE( result == 1 );
    }

    SECTION( "Range of size 2, equal integers" )
    {
        size_t && result = uniqueCount(di.rbegin()+3, di.rbegin()+5);
        INFO( "uniqueCount must return 1" );
        REQUIRE( result == 1 );
    }

    SECTION( "Range of size 2, distinct integers" )
    {
        size_t && result = uniqueCount(di.rbegin()+4, di.rbegin()+6);
        INFO( "uniqueCount must return 2" );
        REQUIRE( result == 2 );
    }

    SECTION( "Range of size 3, equal integers" )
    {
        size_t && result = uniqueCount(di.rbegin()+9, di.rbegin()+12);
        INFO( "uniqueCount must return 1" );
        REQUIRE( result == 1 );
    }

    SECTION( "Range of size 3, two values" )
    {
        size_t && result = uniqueCount(di.rbegin()+8, di.rbegin()+11);
        INFO( "uniqueCount must return 2" );
        REQUIRE( result == 2 );
    }

    SECTION( "Range of size 3, all distinct" )
    {
        size_t && result = uniqueCount(di.rbegin()+7, di.rbegin()+10);
        INFO( "uniqueCount must return 3" );
        REQUIRE( result == 3 );
    }

    SECTION( "Longer range #1" )
    {
        size_t && result = uniqueCount(di.rbegin()+5, di.rbegin()+13);
        INFO( "uniqueCount must return 3" );
        REQUIRE( result == 3 );
    }

    SECTION( "Longer range #2" )
    {
        size_t && result = uniqueCount(di.rbegin()+3, di.rbegin()+15);
        INFO( "uniqueCount must return 4" );
        REQUIRE( result == 4 );
    }

    SECTION( "Longer range #3" )
    {
        size_t && result = uniqueCount(di.rbegin(), di.rend());
        INFO( "uniqueCount must return 5" );
        REQUIRE( result == 5 );
    }

    SECTION( "Very long range #1" )
    {
        deque<int> di2(bigsize, 3);
        size_t && result = uniqueCount(di2.rbegin(), di2.rend());
        INFO( "uniqueCount must return 1" );
        REQUIRE( result == 1 );
    }

    SECTION( "Very long range #2" )
    {
        deque<int> di2(bigsize, 4);
        di2[9000] = 3;
        size_t && result = uniqueCount(di2.rbegin(), di2.rend());
        INFO( "uniqueCount must return 2" );
        REQUIRE( result == 2 );
    }

    SECTION( "Very long range #3" )
    {
        deque<int> di2(bigsize, 5);
        for (size_t i = 0; i < bigsize; i += 2)
            di2[i] = 6;
        size_t && result = uniqueCount(di2.rbegin(), di2.rend());
        INFO( "uniqueCount must return 2" );
        REQUIRE( result == 2 );
    }

    SECTION( "Very long range #4" )
    {
        deque<size_t> dsi2(bigsize);
        for (size_t i = 0; i < bigsize; ++i)
            dsi2[i] = i;
        size_t && result = uniqueCount(dsi2.rbegin(), dsi2.rend());
        INFO( "uniqueCount must return " << bigsize );
        REQUIRE( result == bigsize );
    }

    SECTION( "Strings, equal" )
    {
        vector<string> vs { "abc", "abc" };
        size_t && result = uniqueCount(vs.begin(), vs.end());
        INFO( "uniqueCount must return 1" );
        REQUIRE( result == 1 );
    }

    SECTION( "Strings, distinct" )
    {
        vector<string> vs { "abc", "def" };
        size_t && result = uniqueCount(vs.begin(), vs.end());
        INFO( "uniqueCount must return 2" );
        REQUIRE( result == 2 );
    }
}


TEST_CASE( "Function modExp",
           "[ex-d]" )
{
    // Test data
    vector<vector<int>> tdata {
        {       1,       0,     1,     0 },  // n = 1 cases
        {     100,       0,     1,     0 },
        {     100,     200,     1,     0 },
        {     200,     100,     1,     0 },
        {       1,       0,     2,     1 },  // n > 1, b = 0 cases
        {     100,       0,   200,     1 },
        {     200,       0,   100,     1 },
        {       2,       3,     9,     8 },  // Small cases
        {       2,       3,     5,     3 },
        {       2,       3,     2,     0 },
        {       3,       2,     5,     4 },
        {       3,       2,     2,     1 },
        {   34347,   34839,  2349,  2187 },  // Large cases
        {  349384,  648703,  9384,  7888 },
        { 2387480, 1334858, 10478,  7010 },
        { 8475672, 3647583, 37489, 23184 },
        { 9438573, 9348473, 46300, 46033 },
        {      97,       6,    10,     9 },  // From project description
        { 1234567, 2345678, 45678,   679 },
    };

    for (const auto v : tdata)
    {
        int && result = modExp(v[0], v[1], v[2]);
        INFO( "modExp(" << v[0] << ", " << v[1] << ", " << v[2]
                  << ") should return " << v[3]
                  << ", but it actually returned " << result << "." );
        REQUIRE( result == v[3] );
    }
}

