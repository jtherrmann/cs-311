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

#include <cassert>  // for assert


// ============================================================================
// Non-public function prototypes
// ============================================================================

// countHDT_recurse
// See definition for documentation.
int countHDT_recurse(vector<vector<int>> & board,
		     int dim_x, int dim_y, int empty_squares);

// first_empty
// See definition for documentation.
pair<int, int> first_empty(vector<vector<int>> & board, int dim_x, int dim_y);


// ============================================================================
// Public function definitions
// ============================================================================

// countHDT
// See header for documentation.
int countHDT(int dim_x, int dim_y,
	     int forbid1_x, int forbid1_y,
	     int forbid2_x, int forbid2_y)
{
    vector<vector<int>> board(dim_x, vector<int>(dim_y, 0));
    board[forbid1_x][forbid1_y] = 1;
    board[forbid2_x][forbid2_y] = 1;
    return countHDT_recurse(board, dim_x, dim_y, (dim_x * dim_y) - 2);
}


// ============================================================================
// Non-public function definitions
// ============================================================================

// countHDT_recurse
//
// Return 1 if the given board represents a full solution, otherwise return the
// number of full solutions that can be formed from the given partial solution.
//
// Pre:
// - dim_x > 0
// - dim_y > 0
// - board.size() == dim_x
// - Each vector<int> element of board has size equal to dim_y.
// - For each vector<int> element of board, each int element is 0 or 1.
// - empty_squares is the total number of inner elements equal to 0 (that is,
//   the number of empty squares on the board).
// - 0 <= empty_squares <= (dim_x * dim_y) - 2
//
// Does not throw.
int countHDT_recurse(vector<vector<int>> & board,
		     int dim_x, int dim_y, int empty_squares)
{
    // Check for a full solution.
    if (empty_squares == 0)
	return 1;

    // Find the first empty square.
    auto empty = first_empty(board, dim_x, dim_y);
    int x = empty.first;
    int y = empty.second;

    int total = 0;

    // If a partial solution can be formed by covering the empty square with a
    // horizontally placed domino, count the full solutions that can be formed
    // from the partial solution.
    if (x + 1 < dim_x && board[x + 1][y] == 0) {
	board[x][y] = 1;
	board[x + 1][y] = 1;
	total += countHDT_recurse(board, dim_x, dim_y, empty_squares - 2);
	board[x][y] = 0;
	board[x + 1][y] = 0;
    }

    // Repeat the process with a vertically placed domino.
    if (y + 1 < dim_y && board[x][y + 1] == 0) {
	board[x][y] = 1;
	board[x][y + 1] = 1;
	total += countHDT_recurse(board, dim_x, dim_y, empty_squares - 2);
	board[x][y] = 0;
	board[x][y + 1] = 0;
    }

    return total;
}


// first_empty
//
// Return the coordinates of the first non-empty square on the board.
//
// Pre:
// - dim_x > 0
// - dim_y > 0
// - board.size() == dim_x
// - Each vector<int> element of board has size equal to dim_y.
// - For each vector<int> element of board, each int element is 0 or 1.
// - At least one of the inner elements is 0.
//
// Does not throw.
pair<int, int> first_empty(vector<vector<int>> & board, int dim_x, int dim_y)
{
    for (int y = 0; y < dim_y; ++y) {
	for (int x = 0; x < dim_x; ++x) {
	    if (board[x][y] != 1)
		return make_pair(x, y);
	}
    }
    // This point will never be reached.
    assert (false);
}
