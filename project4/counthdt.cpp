// counthdt.cpp
// Jake Herrmann
// 4 Oct 2018
//
// CS 311 Fall 2018
// Source for Project 4 solution

#include <utility>
using std::make_pair;
using std::pair;

#include <vector>
using std::vector;

// TODO: remove
#include <cassert>


int countHDT_recurse(vector<vector<int>> & board, int dim_x, int dim_y, int empty_squares);
pair<int, int> first_empty(vector<vector<int>> & board, int dim_x, int dim_y);


int countHDT(int dim_x, int dim_y,
	     int forbid1_x, int forbid1_y,
	     int forbid2_x, int forbid2_y)
{
    vector<vector<int>> board(dim_x, vector<int>(dim_y, 0));
    board[forbid1_x][forbid1_y] = 1;
    board[forbid2_x][forbid2_y] = 1;
    return countHDT_recurse(board, dim_x, dim_y, (dim_x * dim_y) - 2);
}


int countHDT_recurse(vector<vector<int>> & board, int dim_x, int dim_y, int empty_squares) {
    if (empty_squares == 0)
	return 1;

    auto empty = first_empty(board, dim_x, dim_y);
    int x = empty.first;
    int y = empty.second;

    int total = 0;

    if (x + 1 < dim_x && board[x + 1][y] == 0) {
	board[x][y] = 1;
	board[x + 1][y] = 1;
	total += countHDT_recurse(board, dim_x, dim_y, empty_squares - 2);
	board[x][y] = 0;
	board[x + 1][y] = 0;
    }

    if (y + 1 < dim_y && board[x][y + 1] == 0) {
	board[x][y] = 1;
	board[x][y + 1] = 1;
	total += countHDT_recurse(board, dim_x, dim_y, empty_squares - 2);
	board[x][y] = 0;
	board[x][y + 1] = 0;
    }

    return total;
}

// TODO: pre: contains at least one empty?
pair<int, int> first_empty(vector<vector<int>> & board, int dim_x, int dim_y) {
    for (int y = 0; y < dim_y; ++y) {
	for (int x = 0; x < dim_x; ++x) {
	    if (board[x][y] != 1)
		return make_pair(x, y);
	}
    }
    // TODO: remove?
    assert (false);
}
