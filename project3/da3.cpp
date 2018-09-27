// da3.cpp
// Jake Herrmann
// 27 Sep 2018
//
// CS 311 Fall 2018
// Source for Project 3 functions

#include "da3.h"


int modExp(int a, int b, int n)
{
    if (n == 1)
	return 0;
    if (b == 0)
	return 1;

    int q = modExp(a, b / 2, n);

    if (b % 2 == 0)
	return (q * q) % n;

    return ((a % n) * ((q * q) % n)) % n;
}

