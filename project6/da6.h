// da6.h
// Jake Herrmann
// 8 Nov 2018 (TODO)
//
// CS 311 Fall 2018
// Header for Project 6 code


// TODO: address TODO/FIXME in file
// TODO: read through project description and coding standards; comment
// sections, classes, functions, etc.


#ifndef FILE_DA6_H_INCLUDED
#define FILE_DA6_H_INCLUDED


#include <cstddef>
// For std::size_t

#include <memory>
// For std::shared_ptr, std::make_shared

#include <utility>
// For std::pair, std::make_pair


#include "llnode2.h"
// For LLNode2


// TODO: comments (name, description, pre, req on types)
//
// TODO: does it need exception safety guarantee?
// Exception neutral, does not throw additional exceptions.
template<typename ValType>
void reverseList(shared_ptr<LLNode2<ValType>> & head) {
    if (head) {
	shared_ptr<LLNode2<ValType>> newhead;
	shared_ptr<LLNode2<ValType>> oldhead = nullptr;
	while (head) {
	    newhead = head;
	    head = head->_next;
	    newhead->_next = oldhead;
	    oldhead = newhead;
	}
	head = newhead;
    }
}


// ============================================================================
// class template ListMap
// ============================================================================

// class template ListMap
// Template for an associative linked list.
//
// Requirements on Types:
// - KType and VType meet the type requirements of std::pair and std::make_pair
//   from <utility>.
// - KType has a public operator== that offers at least the Strong Guarantee.
// - KType has a copy ctor that offers at least the Strong Guarentee.
// - VType has a copy ctor and a copy assignment operator that offer at least
//   the Strong Guarantee.
// - KType and VType have non-throwing dctors.
//
// Invariants:
// - _head is empty or points to the first node of a singly linked list of
//   key-value pairs.
// - Each node in the list stores a key-value pair whose key type is key_type
//   and whose value type is value_type.
// - Each node in the list stores a std::shared_ptr that points to the next
//   node (if one exists).
// - Each key in the list appears only once.
// - 0 <= number of nodes <= maximum value for type size_type.
template <typename KType, typename VType>
class ListMap {

// ListMap: Public member types
public:

    // Type of keys.
    using key_type = KType;

    // Type of associated values.
    using value_type = VType;

    // Type of key-value pairs.
    using kv_type = std::pair<key_type, value_type>;

    // Type of list nodes.
    using node_type = LLNode2<kv_type>;

    // Type of list size.
    using size_type = std::size_t;


// ListMap: Default ctor and the Big Five
public:

    // Default ctor
    // Create an empty list.
    //
    // No-Throw Guarantee
    // Exception neutral, does not throw additional exceptions.
    //
    // Note that std::shared_ptr's default ctor does not throw. Source:
    // https://en.cppreference.com/w/cpp/memory/shared_ptr/shared_ptr
    ListMap() noexcept
	:_head()
    {}

    // Dctor
    //
    // No-Throw Guarantee
    // Exception neutral, does not throw additional exceptions.
    ~ListMap() = default;

    // Copy ctor, move ctor, copy assignment operator, move assignment operator
    ListMap(const ListMap & other) = delete;
    ListMap(ListMap && other) = delete;
    ListMap & operator=(const ListMap & other) = delete;
    ListMap & operator=(ListMap && other) = delete;


// ListMap: General public member functions
public:

    // size
    // Return the number of nodes in the list.
    //
    // Strong Guarantee
    // Exception neutral, does not throw additional exceptions.
    size_type size() const {
	int count = 0;
	auto current = _head;
	while (current) {
	    ++count;
	    current = current->_next;
	}
	return count;
    }

    // empty
    // Return whether the list is empty.
    //
    // No-Throw Guarantee
    // Exception neutral, does not throw additional exceptions.
    bool empty() const {
	return !_head;
    }

    // find
    // If the list contains the given key, return a pointer to the associated
    // value. Otherwise return nullptr.
    //
    // TODO: DRY the bodies somehow? (might have been mentioned in lecture
    // slides early in semester)
    //
    // Strong Guarantee
    // Exception neutral, does not throw additional exceptions.
    value_type * find(key_type key) {
	auto node = lookup(key);
	if (node)
	    return &(node->_data.second);
	return nullptr;
    }
    const value_type * find(key_type key) const {
	auto node = lookup(key);
	if (node)
	    return &(node->_data.second);
	return nullptr;
    }

    // insert
    // Add a key-value pair to the list. If the list already contains the given
    // key, overwrite its associated value with the given value.
    //
    // Pre:
    // - size() < maximum value for type size_type.
    //
    // Strong Guarantee
    // Exception neutral, does not throw additional exceptions.
    void insert(key_type key, value_type value) {
	auto node = lookup(key);
	if (node)
	    node->_data.second = value;
	else {
	    auto newpair = std::make_pair(key, value);
	    auto newnode = node_type(newpair, _head);
	    _head = std::make_shared<node_type>(newnode);
	}
    }

    // erase
    // If the list contains the given key, remove that key-value pair.
    // Otherwise do nothing.
    //
    // Pre:
    // TODO
    //
    // Strong Guarantee
    // Exception neutral, does not throw additional exceptions.
    void erase(key_type key) {
	if (_head) {
	    if (_head->_data.first == key)
		_head = _head->_next;
	    else {
	    	auto current = _head;
	    	while (current->_next) {
	    	    if (current->_next->_data.first == key) {
	    	    	current->_next = current->_next->_next;
			break;
		    }
		    current = current->_next;
	    	}
	    }
	}
    }

    // traverse
    // Call the given function on each key-value pair in the list.
    //
    // Requirements on Types:
    // - Func is either a function pointer or an object for which operator() is
    //   defined.
    // - Func takes two parameters, the first of type key_type and the second
    //   of type value_type, and returns nothing.
    // - Func offers the Strong Guarantee.
    //
    // Pre:
    // TODO
    //
    // Strong Guarantee
    // Exception neutral, does not throw additional exceptions.
    template <typename Func>
    void traverse(Func f) {
	auto current = _head;
	while (current) {
	    f(current->_data.first, current->_data.second);
	    current = current->_next;
	}
    }


// ListMap: Private member functions
private:

    // lookup
    // If the list contains the given key, return a pointer to the node that
    // contains the key-value pair. Otherwise return an empty pointer.
    //
    // Pre:
    // TODO
    //
    // Strong Guarantee
    // Exception neutral, does not throw additional exceptions.
    std::shared_ptr<node_type> lookup(key_type key) const {
	auto current = _head;
	while (current) {
	    if (current->_data.first == key)
		return current;
	    current = current->_next;
	}
	return current;
    }


// ListMap: Private data members
private:

    std::shared_ptr<node_type> _head;


};  // End class template ListMap


#endif  // #ifndef FILE_DA6_H_INCLUDED
