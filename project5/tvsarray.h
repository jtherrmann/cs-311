// tvsarray.h
// Jake Herrmann
// 1 Nov 2018
//
// CS 311 Fall 2018
// Header for class template TVSArray
//
// Based on class VSArray by Glenn G. Chappell.


// TODO: address TODO/FIXME in file
// TODO: all must be exception neutral? and marked as such?
// TODO: read through project description, coding standards, & relevant lecture
// slides


#ifndef FILE_TVSARRAY_H_INCLUDED
#define FILE_TVSARRAY_H_INCLUDED

#include <cstddef>
// For std::size_t

#include <algorithm>
// For std::copy, std::max, std::swap


// ============================================================================
// class template TVSArray: Class template definition
// ============================================================================

// TODO: requirements on types, invariants; others?


// class template TVSArray
// Template for a Very Smart Array.
//
// Resizable, copyable/movable, exception-safe.

// Requirements on Types: TODO
//
// Invariants:
// - 0 <= _size <= _capacity.
// - _data points to an array of value_type, allocated with new[], owned by
//   *this, holding _capacity items. Except: _data may be nullptr, if
//   _capacity == 0.
template <typename T>
class TVSArray {

// TVSArray: Public member types
public:

    // value_type: type of data items
    using value_type = T;

    // size_type: type of sizes & indices
    using size_type = std::size_t;

    // iterator, const_iterator: random-access iterator types
    using iterator = value_type *;
    using const_iterator = const value_type *;

// TVSArray: internal-use constants
private:

    // Capacity of default-constructed object
    enum { DEFAULT_CAP = 16 };

// TVSArray: Ctors and the Big Five
public:

    // Default ctor & ctor from size
    // Strong Guarantee
    //
    // TODO ROT (requirements on types):
    // - VT (value_type) default ctor must offer strong guarantee; for
    //   _data(new...)
    explicit TVSArray(size_type size=0)
        :_capacity(std::max(size, size_type(DEFAULT_CAP))),
            // _capacity must be declared before _data
         _size(size),
         _data(new value_type[_capacity])
    {}

    // Copy ctor
    // Strong Guarantee
    // Exception neutral.
    //
    // TODO ROT:
    // - VT default ctor strong guarantee; for _data(new...)
    TVSArray(const TVSArray & other)
	:_capacity(other._capacity),
	 _size(other._size),
	 _data(new value_type[other._capacity])
    {
	value_type * newdata = new value_type[_capacity];

	try {
	    std::copy(other.begin(), other.end(), newdata);
	}
	catch (...) {
	    delete [] _data;
	    delete [] newdata;
	    throw;
	}

	std::swap(_data, newdata);
	delete [] newdata;
    }

    // Move ctor
    // No-Throw Guarantee
    //
    // TODO ROT:
    // - VT no-throw for move ctor? does _data(other._data) invoke VT's move
    //   ctor?
    TVSArray(TVSArray && other) noexcept
	:_capacity(other._capacity),
	 _size(other._size),
	 _data(other._data)
    {
	other._capacity = 0;
	other._size = 0;
	other._data = nullptr;
    }

    // Copy assignment operator
    // Strong Guarantee
    // Exception neutral.
    TVSArray & operator=(const TVSArray & other)
    {
	TVSArray copy(other);
	swap(copy);
	return *this;
    }

    // Move assignment operator
    // No-Throw Guarantee
    // Exception neutral.
    TVSArray & operator=(TVSArray && other) noexcept
    {
	swap(other);
	return *this;
    }

    // Dctor
    // No-Throw Guarantee
    //
    // TODO ROT:
    // - VT no-throw dctor
    ~TVSArray()
    {
        delete [] _data;
    }

// TVSArray: General public operators
public:

    // TODO ROT

    // operator[] - non-const & const
    // No-Throw Guarantee
    value_type & operator[](size_type index)
    {
        return _data[index];
    }
    const value_type & operator[](size_type index) const
    {
        return _data[index];
    }

// TVSArray: General public member functions
public:

    // TODO ROT

    // size
    // No-Throw Guarantee
    size_type size() const
    {
        return _size;
    }

    // empty
    // No-Throw Guarantee
    bool empty() const
    {
        return size() == 0;
    }

    // begin - non-const & const
    // No-Throw Guarantee
    iterator begin()
    {
        return _data;
    }
    const_iterator begin() const
    {
        return _data;
    }

    // end - non-const & const
    // No-Throw Guarantee
    iterator end()
    {
        return begin() + size();
    }
    const_iterator end() const
    {
        return begin() + size();
    }

    // resize
    //
    // Pre:
    // - newsize >= 0
    //
    // Strong Guarantee
    // Exception neutral.
    void resize(size_type newsize)
    {
	if (newsize <= _capacity)
	    _size = newsize;
	else {
	    size_type newcap = _capacity * 2;
	    if (newcap < newsize)
		newcap = newsize;

	    value_type * newdata = new value_type[newcap];

	    try {
	    	std::copy(begin(), end(), newdata);
	    }
	    catch (...) {
	    	delete [] newdata;
	    	throw;
	    }

	    // TODO:
	    // - https://www.cs.uaf.edu/~chappell/class/2018_fall/cs311/lect/cs311-20181024-generic.pdf
	    //   - slide 24: use std::swap on ALL data members?
	    _size = newsize;
	    _capacity = newcap;
	    std::swap(_data, newdata);
	    delete [] newdata;
	}
    }

    // insert
    // ??? Guarantee (TODO)
    iterator insert(iterator pos, const value_type & item)
    {
	return pos;  // Dummy return
	// TODO: Write this!!!
    }

    // erase
    // ??? Guarantee (TODO)
    iterator erase(iterator pos)
    {
	return pos;  // Dummy return
	// TODO: Write this!!!
    }

    // push_back
    // InsertEnd operation.
    // ??? Guarantee (TODO)
    void push_back(const value_type & item)
    {
        insert(end(), item);
    }

    // pop_back
    // RemoveEnd operation.
    // ??? Guarantee (TODO)
    void pop_back()
    {
        erase(end()-1);
    }

    // swap
    // No-Throw Guarantee
    // Exception neutral.
    void swap(TVSArray & other) noexcept
    {
	std::swap(_capacity, other._capacity);
	std::swap(_size, other._size);
	std::swap(_data, other._data);
    }

// TVSArray: Private data members
private:

    size_type _capacity;  // Size of our allocated array
    size_type _size;  // Size of client's data
    value_type * _data;  // Pointer to array

};  // End class template TVSArray


#endif //#ifndef FILE_TVSARRAY_H_INCLUDED

