#include "product.h"

void Product::setName(std::string name) {
    _name = name;
}

void Product::setInventory(int items) {
    _items = items;
}

std::string Product::getName() const {
    return _name;
}

int Product::getInventory() const {
    return _items;
}

bool Product::empty() const {
    return getInventory() == 0;
}

std::string Product::toString() const {
    return getName() + " (" + std::to_string(getInventory()) + ")";
}

bool Product::operator==(const Product & other) const {
    return getName() == other.getName() && getInventory() == other.getInventory();
}

bool Product::operator!=(const Product & other) const {
    return !(*this == other);
}

// TODO: pre
Product & Product::operator++() {
    ++_items;
    return *this;
}

// TODO: post
Product Product::operator++(int dummy) {
    (void)dummy;
    auto copy = *this;
    ++(*this);
    return copy;
}

// TODO: pre
Product & Product::operator--() {
    if (_items > 0)
	--_items;
    return *this;
}

// TODO: post
Product Product::operator--(int dummy) {
    (void)dummy;
    auto copy = *this;
    --(*this);
    return copy;
}

std::ostream & operator<<(std::ostream & out, const Product & p) {
    out << p.toString();
    return out;
}
