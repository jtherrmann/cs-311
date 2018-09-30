// counthdt.h
// Jake Herrmann
// 4 Oct 2018
//
// CS 311 Fall 2018
// Header for Project 4 solution

#ifndef FILE_COUNTHDT_H_INCLUDED
#define FILE_COUNTHDT_H_INCLUDED

// Pre:
// - 0 <= forbid1_x < dim_x
// - 0 <= forbid1_y < dim_y
// - 0 <= forbid2_x < dim_x
// - 0 <= forbid2_y < dim_y
int countHDT(int dim_x, int dim_y,
	     int forbid1_x, int forbid1_y,
	     int forbid2_x, int forbid2_y);

#endif  //#ifndef FILE_COUNTHDT_H_INCLUDED
