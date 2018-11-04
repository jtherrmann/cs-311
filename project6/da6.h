// da6.h
// Jake Herrmann
// 8 Nov 2018 (TODO)
//
// CS 311 Fall 2018
// Header for Project 6 code


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


template <typename KType, typename VType>  // TODO: correct?
class ListMap {

public:

    using key_type = KType;

    using value_type = VType;

    using size_type = std::size_t;

    // TODO: acceptable solution for kv_type?
    using kv_type = std::pair<KType, VType>;

    using node_type = LLNode2<kv_type>;

public:

    // Default ctor
    ListMap()
	:_head()
    {}

    // Dctor
    // TODO; or default?
    ~ListMap() {}

    ListMap(const ListMap & other) = delete;
    ListMap(ListMap && other) = delete;
    ListMap & operator=(const ListMap & other) = delete;
    ListMap & operator=(ListMap && other) = delete;

public:

    // TODO: confirm not allowed to store size as data member
    size_type size() const {
	int count = 0;
	auto _current = _head;
	while (_current) {
	    ++count;
	    _current = _current->_next;
	}
	return count;
    }

    bool empty() const {
	return !_head;
    }

    // TODO: factor out search method
    // TODO: param passing method?
    value_type * find(key_type key) {
	auto _current = _head;
	while (_current) {
	    if (_current->_data.first == key)
		return &(_current->_data.second);
	    _current = _current->_next;
	}
	return nullptr;
    }
    const value_type * find(key_type key) const {
	auto _current = _head;
	while (_current) {
	    if (_current->_data.first == key)
		return &(_current->_data.second);
	    _current = _current->_next;
	}
	return nullptr;
    }

    // TODO: factor out search method
    // TODO: param passing methods?
    void insert(key_type key, value_type value) {
	auto _current = _head;
	bool done = false;
	while (_current && !done) {
	    if (_current->_data.first == key) {
		_current->_data.second = value;
		done = true;
	    }
	    _current = _current->_next;
	}
	if (!done) {
	    auto newpair = std::make_pair(key, value);
	    auto newnode = node_type(newpair, _head);
	    _head = std::make_shared<node_type>(newnode);
	}
    }

    // TODO: factor out search method
    // TODO: param passing methods?
    void erase(key_type key) {
	// TODO: how to free memory of removed node? or is that handled by
	// shared_ptr?
	if (!empty()) {
	    if (_head->_data.first == key)
		_head = _head->_next;
	    else {
	    	auto _current = _head;
	    	while (_current->_next) {
	    	    if (_current->_next->_data.first == key) {
	    	    	_current->_next = _current->_next->_next;
			break;
		    }
		    _current = _current->_next;
	    	}
	    }
	}
    }

    template <typename Func>
    void traverse(Func f) {
	auto _current = _head;
	while (_current) {
	    f(_current->_data.first, _current->_data.second);
	    _current = _current->_next;
	}
    }



private:

    std::shared_ptr<node_type> _head;

};  // End class template ListMap


#endif  // #ifndef FILE_DA6_H_INCLUDED
