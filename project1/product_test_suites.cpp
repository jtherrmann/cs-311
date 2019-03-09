// product_test_suites.cpp
// Glenn G. Chappell
// 4 Sep 2018
// Updated: 10 Sep 2018
//
// For CS 311 Fall 2018
// Tests for class Product: test suites
// For Project 1, Exercise A
// Uses the "Catch" unit-testing framework, version 2
// Requires product_test_main.cpp, catch.hpp, product.h, product.cpp

// Includes for code to be tested
#include "product.h"       // For class Product
#include "product.h"       // Double inclusion test

#define CATCH_CONFIG_FAST_COMPILE
                           // Disable some features for faster compile
#include "catch.hpp"       // For the "Catch" unit-testing framework

// Additional includes for this test program
#include <string>
using std::string;
#include <ostream>
using std::ostream;
#include <sstream>
using std::ostringstream;
#include <cstddef>
using std::size_t;
#include <utility>
using std::move;


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


// *********************************************************************
// Test Cases
// *********************************************************************


TEST_CASE( "Function return types are correct",
           "[types]" )
{
    Product t1;
    Product t2;

    SECTION( "Copy assn returns Product by ref" )
    {
        Product & r(t1 = t2);  // By-reference check
        (void)r;  // Avoid unused-variable warning
        REQUIRE( TypeCheck<Product>::check(t1 = t2) );
    }

    SECTION( "Move assn returns Product by ref" )
    {
        Product t_movable;
        Product & r(t1 = move(t_movable));  // By-reference check
        (void)r;  // Avoid unused-variable warning
        REQUIRE( TypeCheck<Product>::check(t1 = move(t_movable)) );
    }

    SECTION( "Product::getName returns string by value" )
    {
        string && rr(t1.getName());  // by-value check
        (void)rr;  // Avoid unused-variable warning
        REQUIRE( TypeCheck<string>::check(t1.getName()) );
    }

    SECTION( "Product::getInventory returns int by value" )
    {
        int && rr(t1.getInventory());  // by-value check
        (void)rr;  // Avoid unused-variable warning
        REQUIRE( TypeCheck<int>::check(t1.getInventory()) );
    }

    SECTION( "Product::empty returns bool by value" )
    {
        bool && rr(t1.empty());  // by-value check
        (void)rr;  // Avoid unused-variable warning
        REQUIRE( TypeCheck<bool>::check(t1.empty()) );
    }

    SECTION( "Product::toString returns string by value" )
    {
        string && rr(t1.toString());  // by-value check
        (void)rr;  // Avoid unused-variable warning
        REQUIRE( TypeCheck<string>::check(t1.toString()) );
    }

    SECTION( "Product::operator++ [pre] returns Product by ref" )
    {
        Product & r(++t1);  // By-reference check
        (void)r;  // Avoid unused-variable warning
        REQUIRE( TypeCheck<Product>::check(++t1) );
    }

    SECTION( "Product::operator++ [post] returns Product by value" )
    {
        Product && rr(t1++);  // by-value check
        (void)rr;  // Avoid unused-variable warning
        REQUIRE( TypeCheck<Product>::check(t1++) );
    }

    SECTION( "Product::operator-- [pre] returns Product by ref" )
    {
        Product & r(--t1);  // By-reference check
        (void)r;  // Avoid unused-variable warning
        REQUIRE( TypeCheck<Product>::check(--t1) );
    }

    SECTION( "Product::operator-- [post] returns Product by value" )
    {
        Product && rr(t1--);  // by-value check
        (void)rr;  // Avoid unused-variable warning
        REQUIRE( TypeCheck<Product>::check(t1--) );
    }

    SECTION( "operator==(Product,Product) returns bool by value" )
    {
        bool && rr(t1 == t2);  // by-value check
        (void)rr;  // Avoid unused-variable warning
        REQUIRE( TypeCheck<bool>::check(t1 == t2) );
    }

    SECTION( "operator!=(Product,Product) returns bool by value" )
    {
        bool && rr(t1 != t2);  // by-value check
        (void)rr;  // Avoid unused-variable warning
        REQUIRE( TypeCheck<bool>::check(t1 != t2) );
    }

    SECTION( "operator<<(ostream,Product) returns ostream by ref" )
    {
        ostringstream ostr;
        ostream & r(ostr << t1);  // By-reference check
        (void)r;  // Avoid unused-variable warning
        REQUIRE( TypeCheck<ostream>::check(ostr << t1) );
    }
}


TEST_CASE( "Functions are const-correct (passes if it compiles)",
           "[types]" )
{
    SECTION( "Calling functions on a const Product object" )
    {
        const Product tc1;

        string s1 = tc1.getName();   // Product::getName
        (void)s1;  // Avoid unused-variable warning
        int w = tc1.getInventory();  // Product::getInventory
        (void)w;  // Avoid unused-variable warning
        bool b = tc1.empty();        // Product::empty
        (void)b;  // Avoid unused-variable warning
        string s2 = tc1.toString();  // Product::toString
        (void)s2;  // Avoid unused-variable warning

        REQUIRE( 0 == 0 );           // Section passes if it compiles
    }

    SECTION( "Taking const Product arguments" )
    {
        const Product tc1;
        const Product tc2;

        Product t3 = tc1;            // Copy ctor
        t3 = tc1;                    // Copy assn

        bool b1 = (tc1 == tc2);      // op==(Product,Product)
        (void)b1;  // Avoid unused-variable warning
        bool b2 = (tc1 != tc2);      // op!=(Product,Product)
        (void)b2;  // Avoid unused-variable warning
        ostringstream ostr;
        ostr << tc1;                 // op<<(ostring,Product)

        REQUIRE( 0 == 0 );           // Section passes if it compiles
    }

    SECTION( "Taking const string arguments" )
    {
        const string s;

        Product t(s, 0);             // Data ctor
        t.setName(s);                // Product::setName

        REQUIRE( 0 == 0 );           // Section passes if it compiles
    }
}


TEST_CASE( "Default-constructed Product object: blank name, 0 inventory",
           "[objs]" )
{
    Product t1;

    REQUIRE( t1.getName() == "" );
    REQUIRE( t1.getInventory() == 0 );
    REQUIRE( t1.empty() );

    SECTION( "Set name" )
    {
        t1.setName("abc");

        REQUIRE( t1.getName() == "abc" );
        REQUIRE( t1.getInventory() == 0 );
        REQUIRE( t1.empty() );
    }

    SECTION( "Set inventory" )
    {
        t1.setInventory(20);

        REQUIRE( t1.getName() == "" );
        REQUIRE( t1.getInventory() == 20 );
        REQUIRE( !t1.empty() );
    }

    SECTION( "Set name, inventory" )
    {
        t1.setName("def");
        t1.setInventory(30);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getInventory() == 30 );
        REQUIRE( !t1.empty() );
    }

    SECTION( "Set inventory, name" )
    {
        t1.setInventory(40);
        t1.setName("ghi");

        REQUIRE( t1.getName() == "ghi" );
        REQUIRE( t1.getInventory() == 40 );
        REQUIRE( !t1.empty() );
    }
}


TEST_CASE( "Data-constructed Product object",
           "[objs]" )
{
    Product t1("xyz", 100);

    REQUIRE( t1.getName() == "xyz" );
    REQUIRE( t1.getInventory() == 100 );
    REQUIRE( !t1.empty() );

    SECTION( "Set name" )
    {
        t1.setName("abc");

        REQUIRE( t1.getName() == "abc" );
        REQUIRE( t1.getInventory() == 100 );
        REQUIRE( !t1.empty() );
    }

    SECTION( "Set inventory" )
    {
        t1.setInventory(20);

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getInventory() == 20 );
        REQUIRE( !t1.empty() );
    }

    SECTION( "Set name, inventory" )
    {
        t1.setName("def");
        t1.setInventory(30);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getInventory() == 30 );
        REQUIRE( !t1.empty() );
    }

    SECTION( "Set inventory, name" )
    {
        t1.setInventory(40);
        t1.setName("ghi");

        REQUIRE( t1.getName() == "ghi" );
        REQUIRE( t1.getInventory() == 40 );
        REQUIRE( !t1.empty() );
    }
}


TEST_CASE( "Copied Product objects",
           "[objs]" )
{
    SECTION( "Copy-constructed Product object" )
    {
        Product t1("xyz", 100);
        Product t2 = t1;

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getInventory() == 100 );
        REQUIRE( !t1.empty() );
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getInventory() == 100 );
        REQUIRE( !t2.empty() );

        t2.setName("abc");
        t2.setInventory(10);

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getInventory() == 100 );
        REQUIRE( !t1.empty() );
        REQUIRE( t2.getName() == "abc" );
        REQUIRE( t2.getInventory() == 10 );
        REQUIRE( !t2.empty() );

        t1.setName("def");
        t1.setInventory(20);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getInventory() == 20 );
        REQUIRE( !t1.empty() );
        REQUIRE( t2.getName() == "abc" );
        REQUIRE( t2.getInventory() == 10 );
        REQUIRE( !t2.empty() );
    }

    SECTION( "Copy-assigned Product object" )
    {
        Product t1("xyz", 100);
        Product t2;
        t2 = t1;

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getInventory() == 100 );
        REQUIRE( !t1.empty() );
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getInventory() == 100 );
        REQUIRE( !t2.empty() );

        t2.setName("abc");
        t2.setInventory(10);

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getInventory() == 100 );
        REQUIRE( !t1.empty() );
        REQUIRE( t2.getName() == "abc" );
        REQUIRE( t2.getInventory() == 10 );
        REQUIRE( !t2.empty() );

        t1.setName("def");
        t1.setInventory(20);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getInventory() == 20 );
        REQUIRE( !t1.empty() );
        REQUIRE( t2.getName() == "abc" );
        REQUIRE( t2.getInventory() == 10 );
        REQUIRE( !t2.empty() );
    }
}


TEST_CASE( "String conversions",
           "[strings]" )
{
    Product t1;
    Product t2("xyz", 100);

    SECTION( "Product::toString" )
    {
        REQUIRE( t1.toString() == " (0)" );
        REQUIRE( t2.toString() == "xyz (100)" );
    }

    SECTION( "operator<<(ostream,Product)" )
    {
        ostringstream ostr1;
        ostr1 << t1;
        REQUIRE( ostr1.str() == " (0)" );
        ostringstream ostr2;
        ostr2 << t2;
        REQUIRE( ostr2.str() == "xyz (100)" );
    }
}


TEST_CASE( "Increment & decrement",
           "[operators]" )
{
    Product t1;
    Product t2("xyz", 10);

    SECTION( "Increment ordinary object" )
    {
        Product t3 = (++t2);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getInventory() == 11 );
        REQUIRE( !t2.empty() );
        REQUIRE( t3.getName() == "xyz" );
        REQUIRE( t3.getInventory() == 11 );
        REQUIRE( !t3.empty() );

        Product t4 = (t2++);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getInventory() == 12);
        REQUIRE( !t2.empty() );
        REQUIRE( t4.getName() == "xyz" );
        REQUIRE( t4.getInventory() == 11 );
        REQUIRE( !t4.empty() );

        ++(++t2);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getInventory() == 14 );
        REQUIRE( !t2.empty() );
    }

    SECTION( "Increment object with zero inventory" )
    {
        ++t1;
        REQUIRE( t1.getName() == "" );
        REQUIRE( t1.getInventory() == 1 );
        REQUIRE( !t1.empty() );

        t1++;
        REQUIRE( t1.getName() == "" );
        REQUIRE( t1.getInventory() == 2 );
        REQUIRE( !t1.empty() );
    }

    SECTION( "Decrement ordinary object" )
    {
        Product t3 = (--t2);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getInventory() == 9 );
        REQUIRE( !t2.empty() );
        REQUIRE( t3.getName() == "xyz" );
        REQUIRE( t3.getInventory() == 9 );
        REQUIRE( !t3.empty() );

        Product t4 = (t2--);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getInventory() == 8 );
        REQUIRE( !t2.empty() );
        REQUIRE( t4.getName() == "xyz" );
        REQUIRE( t4.getInventory() == 9 );
        REQUIRE( !t4.empty() );

        --(--t2);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getInventory() == 6 );
        REQUIRE( !t2.empty() );
    }

    SECTION( "Decrement object with zero inventory" )
    {
        --t1;
        REQUIRE( t1.getName() == "" );
        REQUIRE( t1.getInventory() == 0 );
        REQUIRE( t1.empty() );

        t1--;
        REQUIRE( t1.getName() == "" );
        REQUIRE( t1.getInventory() == 0 );
        REQUIRE( t1.empty() );
    }
}


TEST_CASE( "Equality & inequality",
           "[operators]" )
{
    Product t1("abc", 10);  // Base value
    Product t2("abc", 10);  // Same
    Product t3("def", 10);  // Different name
    Product t4("abc", 20);  // Different inventory
    Product t5("def", 20);  // Different name & inventory

    SECTION( "Equality" )
    {
        REQUIRE( t1 == t1 );
        REQUIRE( t1 == t2 );
        REQUIRE( t2 == t1 );
        REQUIRE( !(t1 == t3) );
        REQUIRE( !(t3 == t1) );
        REQUIRE( !(t1 == t4) );
        REQUIRE( !(t4 == t1) );
        REQUIRE( !(t1 == t5) );
        REQUIRE( !(t5 == t1) );
    }

    SECTION( "Inequality" )
    {
        REQUIRE( !(t1 != t1) );
        REQUIRE( !(t1 != t2) );
        REQUIRE( !(t2 != t1) );
        REQUIRE( t1 != t3 );
        REQUIRE( t3 != t1 );
        REQUIRE( t1 != t4 );
        REQUIRE( t4 != t1 );
        REQUIRE( t1 != t5 );
        REQUIRE( t5 != t1 );
    }
}


TEST_CASE( "Large values",
           "[other]" )
{
    const size_t bigname_len = 1000001;
    string bigname(bigname_len, 'x');  // We make this into a long string

    int biginventory = 2147483641;     // Almost greatest 32-bit signed value

    ostringstream ostr;
    ostr << bigname << " (" << biginventory << ")";
    string bigstringform = ostr.str();
                            // String form of Product(bigname, biginventory)

    SECTION( "Construction from large values" )
    {
        Product t1(bigname, biginventory);

        REQUIRE( t1.getName() == bigname );
        REQUIRE( t1.getInventory() == biginventory );
        REQUIRE( !t1.empty() );

        // Check size & prefix first, to avoid enormous error messages
        REQUIRE( t1.toString().size() == bigstringform.size() );
        REQUIRE( t1.toString().substr(0,20) == bigstringform.substr(0,20) );
        REQUIRE( t1.toString() == bigstringform );
    }

    SECTION( "Set functions, passing large values" )
    {
        Product t1;
        t1.setName(bigname);
        t1.setInventory(biginventory);

        REQUIRE( t1.getName() == bigname );
        REQUIRE( t1.getInventory() == biginventory );
        REQUIRE( !t1.empty() );

        // Check size & prefix first, to avoid enormous error messages
        REQUIRE( t1.toString().size() == bigstringform.size() );
        REQUIRE( t1.toString().substr(0,20) == bigstringform.substr(0,20) );
        REQUIRE( t1.toString() == bigstringform );
    }
}


TEST_CASE( "Same-object tests",
           "[other]" )
{
    SECTION("Copy assignment returns *this")
    {
        Product t1;
        Product t2;
        Product & r(t1 = t2);
        REQUIRE( &r == &t1 );
    }

    SECTION("Move assignment returns *this")
    {
        Product t1;
        Product t_movable;
        Product & r(t1 = move(t_movable));
        REQUIRE( &r == &t1 );
    }

    SECTION("pre-increment returns *this")
    {
        Product t1;
        Product & r(++t1);
        REQUIRE( &r == &t1 );
    }

    SECTION("pre-decrement returns *this")
    {
        Product t1;
        Product & r(--t1);
        REQUIRE( &r == &t1 );
    }

    SECTION("post-increment returns copy")
    {
        Product t1;
        Product && rr1(t1++);
        Product && rr2(t1++);
        REQUIRE( &rr1 != &t1 );
        REQUIRE( &rr1 != &rr2 );
    }

    SECTION("post-decrement returns copy")
    {
        Product t1;
        Product && rr1(t1--);
        Product && rr2(t1--);
        REQUIRE( &rr1 != &t1 );
        REQUIRE( &rr1 != &rr2 );
    }

    SECTION("getName returns copy")
    {
        Product t1;
        string && rr1(t1.getName());
        string && rr2(t1.getName());
        REQUIRE( &rr1 != &rr2 );
    }

    SECTION("getInventory returns copy")
    {
        Product t1;
        int && rr1(t1.getInventory());
        int && rr2(t1.getInventory());
        REQUIRE( &rr1 != &rr2 );
    }

    SECTION("empty returns copy")
    {
        Product t1;
        bool && rr1(t1.empty());
        bool && rr2(t1.empty());
        REQUIRE( &rr1 != &rr2 );
    }

    SECTION("operator<< returns original stream")
    {
        ostringstream ostr;
        Product t1;
        ostream & r(ostr << t1);
        REQUIRE( &r == &ostr );
    }
}

