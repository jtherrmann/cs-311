// ssarray.h
// Jake Herrmann
// 18 Sep 2018
//
// CS 311 Fall 2018
// Header for class template SSArray

#ifndef FILE_SSARRAY_H_INCLUDED
#define FILE_SSARRAY_H_INCLUDED

#include <algorithm>
using std::equal;

#include <cstddef>
using std::size_t;

template <typename T>
class SSArray {

public:

    using size_type = size_t;
    using value_type = T;  // TODO: is this correct?

public:

    SSArray(): _size(8), _pointer(new value_type[_size]) {}

    explicit SSArray(int size): _size(size), _pointer(new value_type[_size]) {}

    SSArray(int size, value_type item): _size(size), _pointer(new value_type[_size]) {
	// TODO: std:fill? or is there some way to set all items to `item` just
	// in the ctor initializers?
    }

    ~SSArray() {
	delete [] _pointer;
    }

public:

    // TODO: see intarray.h for help on const bracket operator
    value_type & operator[](size_type index) {
	return _pointer[index];
    }

    const value_type & operator[](size_type index) const {
	return _pointer[index];
    }

    bool operator==(const SSArray & other) const {
	return size() == other.size() && equal(begin(), end(), other.begin());
    }

    bool operator!=(const SSArray & other) const {
	return !(*this == other);
    }

    // TODO: test
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

    bool operator<=(const SSArray & other) const {
	return *this < other || *this == other;
    }

    bool operator>(const SSArray & other) const {
	return !(*this <= other);
    }

    bool operator>=(const SSArray & other) const {
	return !(*this < other);
    }

public:

    value_type size() const {
	return _size;
    }
    
    value_type * begin() {
	return _pointer;
    }

    const value_type * begin() const {
	return _pointer;
    }

    value_type * end() {
	return begin() + size();
    }

    const value_type * end() const {
	return begin() + size();
    }

private:

    size_type _size;
    value_type * _pointer;

};

#endif  //#ifndef FILE_SSARRAY_H_INCLUDED
