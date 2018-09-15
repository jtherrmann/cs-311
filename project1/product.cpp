// product.cpp
// Jake Herrmann
// 11 Sep 2018
//
// CS 311 Fall 2018
// Source for class Product

#include "product.h"  // class Product
#include <string>  // std::string, std::to_string
#include <ostream>  // std::ostream


// ============================================================================
// class Product: Definitions of ctors.
// ============================================================================

// Default ctor.
Product::Product(): _name(""), _items(0) {}

// Two-parameter ctor.
Product::Product(std::string name, int items) {
    setName(name);
    setInventory(items);
}


// ============================================================================
// class Product: Definitions of public operators.
// ============================================================================

// op==
bool Product::operator==(const Product & other) const {
    return (getName() == other.getName()
	    && getInventory() == other.getInventory());
}

// op!=
bool Product::operator!=(const Product & other) const {
    return !(*this == other);
}

// op++ (pre)
Product & Product::operator++() {
    ++_items;
    return *this;
}

// op++ (post)
Product Product::operator++(int dummy) {
    (void)dummy;
    auto copy = *this;
    ++(*this);
    return copy;
}

// op-- (pre)
Product & Product::operator--() {
    if (_items > 0)
	--_items;
    return *this;
}

// op-- (post)
Product Product::operator--(int dummy) {
    (void)dummy;
    auto copy = *this;
    --(*this);
    return copy;
}


// ============================================================================
// class Product: Definitions of member functions.
// ============================================================================

// getName
std::string Product::getName() const {
    return _name;
}

// getInventory
int Product::getInventory() const {
    return _items;
}

// setName
void Product::setName(std::string name) {
    _name = name;
}

// setInventory
void Product::setInventory(int items) {
    _items = items;
}

// empty
bool Product::empty() const {
    return getInventory() == 0;
}

// toString
std::string Product::toString() const {
    return getName() + " (" + std::to_string(getInventory()) + ")";
}


// ============================================================================
// class Product: Definitions of associated global operators.
// ============================================================================

// op<<
std::ostream & operator<<(std::ostream & out, const Product & p) {
    out << p.toString();
    return out;
}
