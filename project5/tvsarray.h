// tvsarray.h
// Jake Herrmann
// 1 Nov 2018
//
// CS 311 Fall 2018
// Header for class template TVSArray
//
// Based on class VSArray by Glenn G. Chappell.


// TODO: address TODO/FIXME in file
// TODO: read through project description, coding standards, & relevant lecture
// slides


#ifndef FILE_TVSARRAY_H_INCLUDED
#define FILE_TVSARRAY_H_INCLUDED

#include <cstddef>
// For std::size_t

#include <algorithm>
// For std::copy, std::max, std::rotate, std::swap


// ============================================================================
// class template TVSArray: Class template definition
// ============================================================================

// TODO: requirements on types, invariants; others?
// - do we actually need to forbid types that throw for move ops?

// TODO: mark all no-throw methods noexcept?


// class template TVSArray
// Template for a Very Smart Array.
//
// Resizable, copyable/movable, exception-safe.

// Requirements on Types:
// - T is a data type for which new[] can allocate memory.
// - T has a default ctor that offers the Strong Guarantee.
// - T has a dctor that offers the No-Throw Guarantee.
// - T* meets the requirements on iterators passed to std::copy and std::rotate
//   from <algorithm>.
//   - https://en.cppreference.com/w/cpp/algorithm/copy
//   - https://en.cppreference.com/w/cpp/algorithm/rotate
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
    // Cannot serve as an implicit type conversion.
    // Strong Guarantee
    // Exception Neutral
    explicit TVSArray(size_type size=0)
        :_capacity(std::max(size, size_type(DEFAULT_CAP))),
            // _capacity must be declared before _data
         _size(size),
         _data(new value_type[_capacity])
    {}

    // Copy ctor
    // Strong Guarantee
    // Exception Neutral
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
    // Exception Neutral
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
    // Exception Neutral
    TVSArray & operator=(const TVSArray & other)
    {
	TVSArray copy(other);
	swap(copy);
	return *this;
    }

    // Move assignment operator
    // No-Throw Guarantee
    // Exception Neutral
    TVSArray & operator=(TVSArray && other) noexcept
    {
	swap(other);
	return *this;
    }

    // Dctor
    // No-Throw Guarantee
    // Exception Neutral
    ~TVSArray()
    {
        delete [] _data;
    }

// TVSArray: General public operators
public:

    // operator[] - non-const & const
    //
    // Pre:
    // - 0 <= index < size()
    //
    // No-Throw Guarantee
    // Exception Neutral
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

    // size
    // No-Throw Guarantee
    // Exception Neutral
    size_type size() const
    {
        return _size;
    }

    // empty
    // No-Throw Guarantee
    // Exception Neutral
    bool empty() const
    {
        return size() == 0;
    }

    // begin - non-const & const
    // No-Throw Guarantee
    // Exception Neutral
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
    // Exception Neutral
    iterator end()
    {
        return begin() + size();
    }
    const_iterator end() const
    {
        return begin() + size();
    }

    // TODO: not strong guarantee / commit method?
    // - https://www.cs.uaf.edu/~chappell/class/2018_fall/cs311/lect/cs311-20181024-generic.pdf
    //   slide 28 (last slide)
    // - but slide 24 says "use the commit-function idea" for resize
    //
    // resize
    //
    // Pre:
    // - newsize >= 0
    //
    // Strong Guarantee
    // Exception Neutral
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
    //
    // Pre:
    // - begin() <= pos <= end()
    //
    // Basic Guarantee
    // Exception Neutral
    iterator insert(iterator pos, const value_type & item)
    {
	size_type index = pos - begin();
	resize(size() + 1);
	iterator newpos = begin() + index;

	iterator last = end() - 1;
	*last = item;

	std::rotate(newpos, last, end());
	return newpos;
    }

    // erase
    //
    // Pre:
    // - begin() <= pos < end()
    //
    // Basic Guarantee
    // Exception Neutral
    iterator erase(iterator pos)
    {
	std::rotate(pos, pos + 1, end());
	resize(size() - 1);
	return pos;
    }

    // push_back
    // InsertEnd operation.
    //
    // Basic Guarantee
    // Exception Neutral
    void push_back(const value_type & item)
    {
        insert(end(), item);
    }

    // pop_back
    // RemoveEnd operation.
    //
    // Basic Guarantee
    // Exception Neutral
    void pop_back()
    {
        erase(end() - 1);
    }

    // swap
    // No-Throw Guarantee
    // Exception Neutral
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

