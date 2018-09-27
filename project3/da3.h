// da3.h
// Jake Herrmann
// 27 Sep 2018
//
// CS 311 Fall 2018
// Header for Project 3 functions
//
// Original skeleton functions and struct LLNode provided by Glenn G. Chappell.

#ifndef FILE_DA3_H_INCLUDED
#define FILE_DA3_H_INCLUDED

#include <algorithm>
using std::sort;
using std::unique;

#include <cstddef>
using std::size_t;

#include <stdexcept>
using std::out_of_range;


// **************************************************************** // *
// Begin DO-NOT-CHANGE section                                      // *
// Do not alter the lines below                                     // *
// **************************************************************** // *
                                                                    // *
                                                                    // *
// struct LLNode                                                    // *
// Linked List node, with client-specified value type               // *
// Invariants:                                                      // *
//     Either _next is nullptr, or _next points to an LLNode,       // *
//      allocated with new, owned by *this.                         // *
// Requirements on Types:                                           // *
//     ValType must have a copy ctor and a (non-throwing) dctor.    // *
template <typename ValType>                                         // *
struct LLNode {                                                     // *
    ValType   _data;  // Data for this node                         // *
    LLNode *  _next;  // Ptr to next node, or nullptr if none       // *
                                                                    // *
    // The following simplify creation & destruction                // *
                                                                    // *
    // 1- & 2-param ctor                                            // *
    // _data is set to data (given). _next is set to next, if       // *
    // given, or nullptr if not.                                    // *
    // Pre:                                                         // *
    //     theNext, if passed, is either nullptr, or else it points // *
    //      to an LLNode allocated with new, with ownership         // *
    //      transferred to *this.                                   // *
    explicit LLNode(const ValType & data,                           // *
                    LLNode * next = nullptr)                        // *
        :_data(data),                                               // *
         _next(next)                                                // *
    {}                                                              // *
                                                                    // *
    // dctor                                                        // *
    // Does delete on _next.                                        // *
    ~LLNode()                                                       // *
    { delete _next; }                                               // *
                                                                    // *
    // No default ctor, copy, or move.                              // *
    LLNode() = delete;                                              // *
    LLNode(const LLNode & other) = delete;                          // *
    LLNode & operator=(const LLNode & other) = delete;              // *
    LLNode(LLNode && other) = delete;                               // *
    LLNode & operator=(LLNode && other) = delete;                   // *
                                                                    // *
};  // End struct LLNode                                            // *
                                                                    // *
                                                                    // *
// **************************************************************** // *
// End DO-NOT-CHANGE section                                        // *
// Do not alter the lines above                                     // *
// **************************************************************** // *


// function template lookup
//
// For 0 <= index < size, where size is the length of the list starting with
// head, return the value of the _data member of the node corresponding to
// index. For other values of index, throw an std::out_of_range exception.
//
// Requirements on Types: see the documentation for struct LLNode.
template <typename ValueType>
ValueType lookup(const LLNode<ValueType> * head, size_t index)
{
    if (index < 0)
	throw out_of_range("index out of bounds: index < 0");
    auto node = head;
    size_t count = 0;
    while (node != nullptr) {
	if (count == index)
	    return node->_data;
	node = node->_next;
	++count;
    }
    throw out_of_range("index out of bounds: index >= size of the list");
}


// function template didItThrow
//
// Call Func with no parameters. If the call throws an exception, set threw to
// true and re-throw the exception; otherwise set threw to false and return.
//
// Requirements on Types:
// - Func is either a function pointer or an object for which operator() is
//   defined. Func can be called with no parameters.
template <typename Func>
void didItThrow(Func f, bool & threw)
{
    try {
	f();
    }
    catch (...) {
	threw = true;
	throw;
    }
    threw = false;
}


// function template uniqueCount
//
// Return the number of unique values in the given range.
//
// Pre:
// - operator< and operator== are defined for the type of the values in the
//   range. operator== is an equivalence relation.
// - The range is mutable.
//
// Requirements on Types:
// - RAIter meets the type requirements of std::sort and std::unique from
//   <algorithm>. See:
//   - https://en.cppreference.com/w/cpp/algorithm/sort
//   - https://en.cppreference.com/w/cpp/algorithm/unique
template <typename RAIter>
size_t uniqueCount(RAIter first, RAIter last)
{
    // std::unique removes duplicate consecutive elements and returns the
    // resulting range's upper bound iterator.
    // Adapted from: https://stackoverflow.com/a/28100858/10402025
    sort(first, last);
    return unique(first, last) - first;
}


// modExp
//
// Return (a raised to the power of b) mod n.
//
// Does not throw.
//
// Pre:
// - a >= 1
// - b >= 0
// - n >= 1
int modExp(int a, int b, int n);


#endif  //#ifndef FILE_DA3_H_INCLUDED

