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
// - read through the code one more time before submitting
// - test the final version before submitting

// ============================================================================
// class template Product: Class template definition
// ============================================================================

// class template SSArray
// A somewhat smart array.
//
// Requirements on Types:
//     - T is a data type for which new[] can allocate memory.
//     - T has a public dctor.
//     - T* meets the requirements on iterators passed to std::copy and
//       std::fill from <algorithm> (and T meets the requirements on the third
//       parameter passed to std::fill). In particular, T has a public copy
//       ctor. Also see: http://www.cplusplus.com/reference/algorithm/copy/ and
//       http://www.cplusplus.com/reference/algorithm/fill/
//
// Invariants:
//     - _size >= 0
//     - _pointer points to memory allocated with new[]; the memory is owned by
//       *this and holds _size items of type value_type.
//
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
    // Promises to throw no exceptions.
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
    // Promises to throw no exceptions.
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
    // Swap the _size and _pointer data members of the two arrays.
    // Promises to throw no exceptions.
    void mswap(SSArray & other) noexcept {
	swap(_size, other._size);
	swap(_pointer, other._pointer);
    }

};  // End class template SSArray


// ============================================================================
// class template Product: Associated global operators
// ============================================================================

// op==
// Compare the two arrays' sizes and items. Return true if equal and false
// otherwise.
// Requirements on Types:
//     T* meets the requirements on iterators passed to std::equal from
//     <algorithm>. In particular, T has a public operator==. Also see:
//     http://www.cplusplus.com/reference/algorithm/equal/
template <typename T>
bool operator==(const SSArray<T> & first, const SSArray<T> & second) {
    return (first.size() == second.size()
	    && equal(first.begin(), first.end(), second.begin()));
}

// op!=
// Requirements on Types:
//     See documentation for global operator== (above).
template <typename T>
bool operator!=(const SSArray<T> & first, const SSArray<T> & second) {
    return !(first == second);
}

// op<
// Compare the two arrays' items in lexicographic order. Return true if first <
// second and false otherwise.
// Requirements on Types:
//     T has a public operator!= and a public operator<.
template <typename T>
bool operator<(const SSArray<T> & first, const SSArray<T> & second) {
    auto it1 = first.begin();
    auto it2 = second.begin();
    while(it1 != first.end() && it2 != second.end()) {
	if(*it1 != *it2)
	    return *it1 < *it2;
	++it1;
	++it2;
    }
    return first.size() < second.size();
}

// op<=
// Requirements on Types:
//     See documentation for global operator< and global operator== (above).
template <typename T>
bool operator<=(const SSArray<T> & first, const SSArray<T> & second) {
    return first < second || first == second;
}

// op>
// Requirements on Types:
//     See documentation for global operator<= (above).
template <typename T>
bool operator>(const SSArray<T> & first, const SSArray<T> & second) {
    return !(first <= second);
}

// op>=
// Requirements on Types:
//     See documentation for global operator< (above).
template <typename T>
bool operator>=(const SSArray<T> & first, const SSArray<T> & second) {
    return !(first < second);
}


#endif  //#ifndef FILE_SSARRAY_H_INCLUDED
