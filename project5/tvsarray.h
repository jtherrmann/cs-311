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


#ifndef FILE_TVSARRAY_H_INCLUDED
#define FILE_TVSARRAY_H_INCLUDED

#include <cstddef>
// For std::size_t

#include <algorithm>
// For std::copy, std::max


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
    //
    // TODO ROT:
    // - VT default ctor strong guarantee; for _data(new...)
    // - what VT methods called by begin, end, std::copy?
    TVSArray(const TVSArray & other)
	:_capacity(other._capacity),
	 _size(other._size),
	 _data(new value_type[other._capacity])
    {
	std::copy(other.begin(), other.end(), begin());
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
    // ??? Guarantee (TODO)
    //
    // TODO ROT
    TVSArray & operator=(const TVSArray & other)
    {
	return *this;  // Dummy return
	// TODO: Write this!!!
    }

    // Move assignment operator
    // No-Throw Guarantee
    //
    // TODO ROT
    TVSArray & operator=(TVSArray && other) noexcept
    {
	return *this;  // Dummy return
	// TODO: Write this!!!
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
    // ??? Guarantee (TODO)
    void resize(size_type newsize)
    {
	// TODO: Write this!!!
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
    void swap(TVSArray & other) noexcept
    {
	// TODO: Write this!!!
    }

// TVSArray: Private data members
private:

    size_type _capacity;  // Size of our allocated array
    size_type _size;  // Size of client's data
    value_type * _data;  // Pointer to array

};  // End class template TVSArray


#endif //#ifndef FILE_TVSARRAY_H_INCLUDED

