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

bool Product::operator==(const Product & other) {
    return getName() == other.getName() && getInventory() == other.getInventory();
}

bool Product::operator!=(const Product & other) {
    return !(*this == other);
}
