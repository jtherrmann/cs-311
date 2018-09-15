// ssarray.h
// Jake Herrmann
// 18 Sep 2018
//
// CS 311 Fall 2018
// Header for class template SSArray

#ifndef FILE_SSARRAY_H_INCLUDED
#define FILE_SSARRAY_H_INCLUDED

#include <cstddef>
using std::size_t;

template <typename T>
class SSArray {

public:

    using size_type = size_t;
    using value_type = T;  // TODO: is this correct?

public:

    SSArray(): _size(8), _pointer(new value_type[_size]) {}

    SSArray(int size): _size(size), _pointer(new value_type[_size]) {}

    SSArray(int size, value_type item): _size(size), _pointer(new value_type[_size]) {
	// TODO: std:fill? or is there some way to set all items to `item` just
	// in the ctor initializers?
    }

public:

    // TODO: see intarray.h for help on const bracket operator
    value_type & operator[](size_type index) {
	return _pointer[index];
    }

public:

    value_type size() {
	return _size;
    }
    
    value_type * begin() {
	return _pointer;
    }

    value_type * end() {
	return begin() + size();
    }

private:

    size_type _size;
    value_type * _pointer;

};

#endif  //#ifndef FILE_SSARRAY_H_INCLUDED
