// TODO toplevel docs, credit chappell

// cuber_test_suites.cpp  INCOMPLETE
// Glenn G. Chappell
// 27 Nov 2018
//
// For CS 311 Fall 2018
// Tests for class Cuber: test suites
// For Project 8, Exercise B
// Uses the "Catch" unit-testing framework, version 2
// Requires cuber_test_main.cpp, catch.hpp, cuber.h

// Includes for code to be tested
#include "cuber.h"         // For class Cuber
#include "cuber.h"         // Double inclusion test

#define CATCH_CONFIG_FAST_COMPILE
                             // Disable some features for faster compile
#include "catch.hpp"         // For the "Catch" unit-testing framework

// Additional includes for this test program


// *********************************************************************
// Test Cases
// *********************************************************************

TEST_CASE("Cuber: const & non-const")
{
    const Cuber cc_const;
    {
	INFO("5 cubed is 125");
	REQUIRE(cc_const(5) == 125);
    }

    Cuber cc;
    {
	INFO("5 cubed is 125");
	REQUIRE(cc(5) == 125);
    }
}


TEST_CASE("Cuber: wide range of values")
{
    Cuber cc;
    int nums[] = {3, 15, 67, 196, 583, 921, 1000};
    int cubes[] = {27, 3375, 300763, 7529536, 198155287, 781229961, 1000000000};
    for (int i = 0; i < 7; ++i) {
	INFO(nums[i] << " cubed is " << cubes[i]);
	REQUIRE(cc(nums[i]) == cubes[i]);
    }
}


TEST_CASE("Cuber: negative values")
{
    Cuber cc;
    {
	INFO("-5 cubed is -125");
	REQUIRE(cc(-5) == -125);
    }
    {
	INFO("-48 cubed is -110592");
	REQUIRE(cc(-48) == -110592);
    }
}


TEST_CASE("Cuber: floats")
{
    Cuber cc;
    {
	INFO("1.1 is approx. 1.331");
	REQUIRE(cc(1.1) == Approx(1.331));
    }
    {
	INFO("25.372 is approx. 16332.930");
	REQUIRE(cc(25.372) == Approx(16332.930));
    }
    {
	INFO("-61.539 is approx. -233051.179");
	REQUIRE(cc(-61.539) == Approx(-233051.179));
    }
}


TEST_CASE("Cuber: chars")
{
    Cuber cc;
    char arg = 5;
    int result = 125;
    INFO(arg << " cubed is " << result);
    REQUIRE(cc(arg) == result);
}


TEST_CASE("Cuber: special cases")
{
    Cuber cc;
    {
	INFO("0 cubed is 0");
	REQUIRE(cc(0) == 0);
    }
    {
	INFO("1 cubed is 1");
	REQUIRE(cc(1) == 1);
    }
    {
	INFO("-1 cubed is -1");
	REQUIRE(cc(-1) == -1);
    }
}
