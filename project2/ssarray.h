// ssarray.h
// Jake Herrmann
// 18 Sep 2018
//
// CS 311 Fall 2018
// Header for class template SSArray

#ifndef FILE_SSARRAY_H_INCLUDED
#define FILE_SSARRAY_H_INCLUDED

// TODO: remove
#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>
using std::copy;
using std::equal;
using std::fill;
using std::swap;

#include <cstddef>
using std::size_t;

template <typename T>
class SSArray {

public:

    using size_type = size_t;
    using value_type = T;  // TODO: is this correct?

public:

    SSArray(): _size(8), _pointer(new value_type[_size]) {}

    explicit SSArray(int size)
	:_size(size), _pointer(new value_type[_size])
    {}

    SSArray(int size, value_type value)
	:_size(size), _pointer(new value_type[_size])
    {
	fill(begin(), end(), value);
    }

    // dctor
    ~SSArray() {
	delete [] _pointer;
    }

    // copy ctor
    SSArray(const SSArray & other)
	:_size(other._size), _pointer(new value_type[_size])
    {
	// TODO: remove
	cout << "COPY" << endl;
	
	copy(other.begin(), other.end(), begin());
    }

    // move ctor
    SSArray(SSArray && other) noexcept
    	:_size(other._size), _pointer(other._pointer)
    {
    	// TODO: remove
    	cout << "MOVE" << endl;

	other._pointer = nullptr;
    }

    // copy assign
    SSArray & operator=(const SSArray & other) {
	// TODO: remove
	cout << "COPY ASSIGN" << endl;
	
	SSArray copy(other);
	mswap(copy);
	return *this;
    }

    // move assign
    // TODO: test more
    SSArray & operator=(SSArray && other) noexcept {
	// TODO: remove
	cout << "MOVE ASSIGN" << endl;
	
	mswap(other);
	return * this;
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

    size_type size() const {
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

private:

    void mswap(SSArray & other) noexcept {
	swap(_size, other._size);
	swap(_pointer, other._pointer);
    }

};

#endif  //#ifndef FILE_SSARRAY_H_INCLUDED
