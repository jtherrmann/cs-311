// ssarray.h
// Jake Herrmann
// 20 Sep 2018
//
// CS 311 Fall 2018
// Header for class template SSArray

#ifndef FILE_SSARRAY_H_INCLUDED
#define FILE_SSARRAY_H_INCLUDED

#include <algorithm>
using std::copy;
using std::equal;
using std::fill;
using std::swap;

#include <cstddef>
using std::size_t;

// TODO:
// - how to follow coding standard 3A?
// - document noexcept?
// - search for TODO in this file
// - wait until project 1 is graded, apply feedback to project 2
// - read through the code one more time before submitting
// - test the final version before submitting

// class template SSArray
// A somewhat smart array.
// Invariants:
//     - _size >= 0
//     - _pointer points to dynamically allocated memory that is owned by *this
//       and holds _size items of type value_type.
//     - size_type is std::size_t from <cstddef>.  TODO: only necessary if this can change? (or is non-obvious?)
//     - value_type is the specified template parameter.  TODO: only necessary if this can change? (or is non-obvious?)
template <typename T>
class SSArray {

// SSArray: Public member types.
public:

    using size_type = size_t;
    using value_type = T;

// SSArray: Ctors and the Big Five.
public:

    // Default ctor.
    // Initialize the array with 8 items.
    SSArray(): _size(8), _pointer(new value_type[_size]) {}

    // Ctor from size.
    // Initialize the array with size items.
    // Cannot serve as an implicit type conversion.
    // Pre:
    //     size >= 0
    explicit SSArray(size_type size)
	:_size(size), _pointer(new value_type[_size])
    {}

    // Ctor from size and initial value.
    // Initialize the array with size items, each set to value.
    // Pre:
    //     size >= 0
    SSArray(size_type size, value_type value)
	:_size(size), _pointer(new value_type[_size])
    {
	fill(begin(), end(), value);
    }

    // Dctor
    // Release dynamically allocated memory.
    ~SSArray() {
	delete [] _pointer;
    }

    // Copy ctor
    SSArray(const SSArray & other)
	:_size(other._size), _pointer(new value_type[_size])
    {
	copy(other.begin(), other.end(), begin());
    }

    // Move ctor
    SSArray(SSArray && other) noexcept
    	:_size(other._size), _pointer(other._pointer)
    {
	other._pointer = nullptr;
    }

    // op= (copy)
    SSArray & operator=(const SSArray & other) {
	SSArray copy(other);
	mswap(copy);
	return *this;
    }

    // op= (move)
    SSArray & operator=(SSArray && other) noexcept {
	mswap(other);
	return * this;
    }
	

// SSArray: General public operators.
public:

    // op[] (non-const and const)
    // Pre:
    //     0 <= index < _size
    value_type & operator[](size_type index) {
	return _pointer[index];
    }
    const value_type & operator[](size_type index) const {
	return _pointer[index];
    }

    // op==
    // Compare the two arrays' sizes and items. Return true if equal and false
    // otherwise.
    bool operator==(const SSArray & other) const {
	return size() == other.size() && equal(begin(), end(), other.begin());
    }

    // op!=
    bool operator!=(const SSArray & other) const {
	return !(*this == other);
    }

    // op<
    // Compare the two arrays' items in lexicographic order. Return true if
    // *this < other and false otherwise.
    bool operator<(const SSArray & other) const {
	auto it1 = begin();
	auto it2 = other.begin();
	while(it1 != end() && it2 != other.end()) {
	    if(*it1 != *it2)
		return *it1 < *it2;
	    ++it1;
	    ++it2;
	}
	return size() < other.size();
    }

    // op<=
    bool operator<=(const SSArray & other) const {
	return *this < other || *this == other;
    }

    // op>
    bool operator>(const SSArray & other) const {
	return !(*this <= other);
    }

    // op>=
    bool operator>=(const SSArray & other) const {
	return !(*this < other);
    }

// SSArray: Public member functions.
public:

    // size
    // Return the array's size.
    size_type size() const {
	return _size;
    }
    
    // begin (non-const and const)
    // Return a pointer to the first item in the array.
    value_type * begin() {
	return _pointer;
    }
    const value_type * begin() const {
	return _pointer;
    }

    // end (non-const and const)
    // Return a pointer to one position past the last item in the array.
    value_type * end() {
	return begin() + size();
    }
    const value_type * end() const {
	return begin() + size();
    }

// SSArray: Private data members.
private:

    size_type _size;
    value_type * _pointer;

// SSArray: Private member functions.
private:

    // mswap
    // TODO
    // TODO: both need to have the same size (in addition to value type)? if not, swap sizes...?
    void mswap(SSArray & other) noexcept {
	swap(_size, other._size);
	swap(_pointer, other._pointer);
    }

};

#endif  //#ifndef FILE_SSARRAY_H_INCLUDED
