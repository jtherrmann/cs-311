// da3.cpp  SKELETON
// Glenn G. Chappell
// 21 Sep 2018
//
// For CS 311 Fall 2018
// Source for Project 3 Functions

#include "da3.h"       // For Project 3 prototypes & templates


// TODO: document (in header; esp. precond.)
int modExp(int a,
           int b,
           int n)
{
    if (n == 1)
	return 0;
    if (b == 0)
	return 1;

    int q = modExp(a, b/2, n);

    if (b % 2 == 0)
	return (q * q) % n;

    return ((a % n) * ((q * q) % n)) % n;
}

