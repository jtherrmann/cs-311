// treesort.h
// Jake Herrmann
// 19 Nov 2018
//
// CS 311 Fall 2018
// Header for function template treesort (TODO: and other stuff)
// There is no associated source file.


// TODO:
// - address TODO/FIXME in file
// - read through code & comments again


#ifndef FILE_TREESORT_H_INCLUDED
#define FILE_TREESORT_H_INCLUDED


#include <iterator>
using std::iterator_traits;

#include <memory>
using std::shared_ptr;
using std::make_shared;


// struct BSTNode
// Binary Search Tree node
//
// Invariants:
// - _left is empty or _left->_data < _data
// - _right is empty or !(_right->_data < _data)
//
// Requirements on Types:
// - ValType has a public copy ctor that offers the Strong Guarantee.
// - ValType has a non-throwing dctor.
template <typename ValType>
struct BSTNode {

    ValType _data;               // Data for this node.
    shared_ptr<BSTNode> _left;   // Pointer to left child, or empty if none.
    shared_ptr<BSTNode> _right;  // Pointer to right child, or empty if none.

    // 1-parameter ctor
    // Cannot serve as an implicit type conversion.
    //
    // Strong Guarantee
    // Exception neutral, does not throw additional exceptions.
    explicit BSTNode(const ValType & data)
        :_data(data), _left(), _right()
    {}

    // Dctor
    // No-Throw Guarantee
    ~BSTNode() = default;
};


// insert
// Insert item into the Binary Search Tree rooted at root.
//
// Requirements on Types:
// - ValType has a public operator< that offers the Strong Guarantee.
// - ValType meets the ValType requirements of BSTNode.
//
// Strong Guarantee
// Exception neutral, does not throw additional exceptions.
template<typename ValType>
void insert(shared_ptr<BSTNode<ValType>> & root, const ValType & item) {
    if (!root)
	root = make_shared<BSTNode<ValType>>(BSTNode<ValType>(item));
    else if (item < root->_data)
	insert(root->_left, item);
    else
	insert(root->_right, item);
}


// inorder_copy
// Copy the data items, in order, from the Binary Search Tree rooted at root to
// the space beginning at iter. If root is empty, do nothing.
//
// Requirements on Types:
// - ValType is iterator_traits<FDIter>::value_type.
// - ValType has a public copy assignment operator.
// - FDIter has a public operator*.
// - FDIter has a public operator++ (postfix).
// - Each of the above operators offers the Strong Guarantee.
//
// Strong Guarantee
// Exception neutral, does not throw additional exceptions.
template<typename ValType, typename FDIter>
void inorder_copy(shared_ptr<BSTNode<ValType>> root, FDIter & iter) {
    if (root) {
	inorder_copy(root->_left, iter);
	*iter++ = root->_data;
	inorder_copy(root->_right, iter);
    }
}


// treesort
// Perform a stable Treesort on the given range.
//
// Pre:
// - If first != last, then first points to the first item in the range and
//   last points to one position beyond the last item. Otherwise, the range is
//   empty.
//
// Requirements on Types:
// - FDIter has a public copy ctor. (TODO: when is copy ctor called?)
// - FDIter has a public operator!=.
// - FDIter has a public operator++ (prefix).
// - FDIter meets the FDIter requirements of inorder_copy.
// - iterator_traits<FDIter>::value_type meets the ValType requirements of
//   insert and inorder_copy.
// - Each of the above operators offers the Strong Guarantee.
//
// Strong Guarantee
// Exception neutral, does not throw additional exceptions.
template<typename FDIter>
void treesort(FDIter first, FDIter last) {
    using ValType = typename iterator_traits<FDIter>::value_type;
    auto root = shared_ptr<BSTNode<ValType>>();
    for (auto it = first; it != last; ++it)
    	insert(root, *it);
    inorder_copy(root, first);
}


#endif //#ifndef FILE_TREESORT_H_INCLUDED
