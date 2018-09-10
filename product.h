// product.h
// Jake Herrmann
// CS 311 Fall 2018
// 11 Sep 2018

#ifndef FILE_PRODUCT_H_INCLUDED
#define FILE_PRODUCT_H_INCLUDED

// TODO: include string again in header file and move to_string comment to there?
#include <string>  // std::string, std::to_string

// TODO: include ostream again in header file?
#include <ostream>  // std::ostream

class Product {

public:

    // TODO: implement constructors in product.cpp instead?
    // TODO: use 'this' for clarity?

    Product(): _name(""), _items(0) {}

    Product(std::string name, int items) {
    	setName(name);
    	setInventory(items);
    }

    ~Product() = default;
    Product(const Product & other) = default;
    Product(Product && other) = default;
    Product & operator=(const Product & other) = default;
    Product & operator=(Product && other) = default;

    void setName(std::string name);
    void setInventory(int items);

    std::string getName() const;
    int getInventory() const;

    bool empty() const;

    std::string toString() const;

    bool operator==(const Product & other) const;
    bool operator!=(const Product & other) const;

    // TODO: pre
    Product & operator++();

    // TODO: post
    Product operator++(int dummy);

    // TODO: pre
    Product & operator--();

    // TODO: post
    Product operator--(int dummy);
	

private:

    std::string _name;
    int _items;

};  // End class Product.


std::ostream & operator<<(std::ostream & out, const Product & p);


#endif  //#ifndef FILE_PRODUCT_H_INCLUDED