#include "product.h"
#include "product.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main() {
    Product p;
    Product p2("book", 3);

    cout << "name: " << "" << " items: " << 0 << endl;
    cout << "name: " << p.getName() << " items: " << p.getInventory() << endl;

    cout << " (0)" << endl;
    cout << p.toString() << endl;

    cout << "empty: " << 1 << endl;
    cout << "empty: " << p.empty() << endl;

    cout << endl;

    cout << "name: " << "book" << " items: " << 3 << endl;
    cout << "name: " << p2.getName() << " items: " << p2.getInventory() << endl;

    cout << "book (3)" << endl;
    cout << p2.toString() << endl;

    cout << "empty: " << 0 << endl;
    cout << "empty: " << p2.empty() << endl;

    cout << endl;

    Product p3;
    Product p4("book", 3);

    cout << "p == p3: " << 1 << endl;
    cout << (p == p3) << endl;

    cout << "p != p3: " << 0 << endl;
    cout << (p != p3) << endl;

    cout << "p != p2: " << 1 << endl;
    cout << (p != p2) << endl;

    cout << endl;

    cout << "p2 == p4: " << 1 << endl;
    cout << (p2 == p4) << endl;

    cout << "p2 != p4: " << 0 << endl;
    cout << (p2 != p4) << endl;
}
