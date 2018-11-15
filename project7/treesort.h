// treesort.h
// Jake Herrmann
// 14 Nov 2018 (TODO)
//
// CS 311 Fall 2018
// Header for function template treesort (TODO: and other stuff)
// There is no associated source file.


// TODO:
// - address TODO/FIXME in file
// - document everything
// - read through project guidelines and coding standards


#ifndef FILE_TREESORT_H_INCLUDED
#define FILE_TREESORT_H_INCLUDED


#include <iterator>
using std::iterator_traits;

#include <memory>
using std::shared_ptr;
using std::make_shared;


// TODO: document (see llnode2.h)
template <typename ValType>
struct BSTNode {
    ValType _data;
    shared_ptr<BSTNode> _left;
    shared_ptr<BSTNode> _right;

    explicit BSTNode(const ValType & data)
        :_data(data), _left(), _right()
    {}

    ~BSTNode() = default;
};


// TODO:
// - make sure is stable
// - pass item by ref-to-const? or pass the iter to the item?
template<typename ValType>
void insert(shared_ptr<BSTNode<ValType>> & root, ValType item) {
    if (!root)
	root = make_shared<BSTNode<ValType>>(BSTNode<ValType>(item));
    else if (item < root->_data)
	insert(root->_left, item);
    else
	insert(root->_right, item);
}


template<typename ValType, typename FDIter>
void inorder_copy(shared_ptr<BSTNode<ValType>> root, FDIter & iter) {
    if (root) {
	inorder_copy(root->_left, iter);
	*iter++ = root->_data;
	inorder_copy(root->_right, iter);
    }
}


template<typename FDIter>
void treesort(FDIter first, FDIter last) {
    using ValType = typename iterator_traits<FDIter>::value_type;
    auto root = shared_ptr<BSTNode<ValType>>();
    for (auto it = first; it != last; ++it)
    	insert(root, *it);
    inorder_copy(root, first);
}


#endif //#ifndef FILE_TREESORT_H_INCLUDED
