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
// For std::shared_ptr

#include <tuple>
// For std::tuple


#include "llnode2.h"


template<typename ValType>
void reverseList(shared_ptr<LLNode2<ValType>> & head) {
    // TODO: write this
}


template <typename KType, typename VType>  // TODO: correct?
class ListMap {

public:

    using key_type = KType;

    using value_type = VType;

    using size_type = std::size_t;

    // TODO: acceptable solution for kv_type?
    using kv_type = std::tuple<KType, VType>;

public:

    // Default ctor
    // TODO
    ListMap() {}

    // Dctor
    // TODO; or default?
    ~ListMap() {}

    ListMap(const ListMap & other) = delete;
    ListMap(ListMap && other) = delete;
    ListMap & operator=(const ListMap & other) = delete;
    ListMap & operator=(ListMap && other) = delete;

public:

    size_type size() const {
	// TODO
	return 0;
    }

    bool empty() const {
	//TODO
	return true;
    }

    // TODO: how to make const version?
    // TODO: param passing method?
    value_type * find(key_type key) const {
	//TODO
	return nullptr;
    }

    // TODO: param passing methods?
    void insert(key_type key, value_type value) {
	//TODO
    }

    // TODO: param passing methods?
    void erase(key_type key) {
	//TODO
    }

    template <typename Func>
    void traverse(Func f) {
	//TODO
    }



private:

    std::shared_ptr<LLNode2<kv_type>> _head;  // TODO: appropriate name?

};  // End class template ListMap


#endif  // #ifndef FILE_DA6_H_INCLUDED
