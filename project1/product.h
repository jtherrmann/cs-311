// product.h
// Jake Herrmann
// 11 Sep 2018
//
// CS 311 Fall 2018
// Header for class Product

#ifndef FILE_PRODUCT_H_INCLUDED
#define FILE_PRODUCT_H_INCLUDED

#include <string>  // std::string
#include <ostream>  // std::ostream


// ============================================================================
// class Product: Class definition.
// ============================================================================

// class Product
// A product: name and number of items in inventory.
// Invariants:
//     _items >= 0
class Product {

// Product: Ctors and the Big Five.
public:

    // Default ctor.
    // Set name to "" and number of items to 0.
    Product();

    // Ctor from name and number of items.
    // Pre:
    //     items >= 0
    Product(std::string name, int items);

    // Use compiler-generated versions of the Big Five.
    ~Product() = default;
    Product(const Product & other) = default;
    Product(Product && other) = default;
    Product & operator=(const Product & other) = default;
    Product & operator=(Product && other) = default;

// Product: Public operators.
public:

    // op==
    // Compare the two products' names and number of items. Return true if
    // equal and false otherwise.
    bool operator==(const Product & other) const;

    // op!=
    // Compare the two products' names and number of items. Return true if not
    // equal and false otherwise.
    bool operator!=(const Product & other) const;

    // op++ (pre)
    // Increase number of items by one.
    Product & operator++();

    // op++ (post)
    // Increase number of items by one.
    Product operator++(int dummy);

    // op-- (pre)
    // Decrease number of items by one.
    Product & operator--();

    // op-- (post)
    // Decrease number of items by one.
    Product operator--(int dummy);

// Product: Member functions.
public:

    // getName
    // Return the product's name.
    std::string getName() const;

    // getInventory
    // Return the number of items in the inventory.
    int getInventory() const;

    // setName
    // Set the product's name.
    void setName(std::string name);

    // setInventory
    // Set the number of items in the inventory.
    // Pre:
    //     items >= 0
    void setInventory(int items);

    // empty
    // Return true if the number of items is zero and false otherwise.
    bool empty() const;

    // toString
    // Return a string representation of the product's name and number of
    // items.
    std::string toString() const;

// Product: Data members.
private:

    // The product's name.
    std::string _name;

    // Number of items in inventory.
    int _items;

};  // End class Product.


// ============================================================================
// class Product: Associated global operators.
// ============================================================================

// op<<
// Print the product's name and number of items.
std::ostream & operator<<(std::ostream & out, const Product & p);


#endif  //#ifndef FILE_PRODUCT_H_INCLUDED
