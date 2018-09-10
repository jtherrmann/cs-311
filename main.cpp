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

    cout << endl;
    
    // Product pen("pen", 5);
    // Product pensame = ++pen;

    // cout << 6 << 6 << endl;
    // cout << pen.toString() << endl;
    // cout << pensame.toString() << endl;

    // Product pen2("pen", 5);
    // Product penlag = pen2++;
    
    // cout << 6 << 5 << endl;
    // cout << pen2.toString() << endl;
    // cout << penlag.toString() << endl;

    Product pen("pen", 5);
    Product pensame = --pen;

    cout << 4 << 4 << endl;
    cout << pen.toString() << endl;
    cout << pensame.toString() << endl;

    Product pen2("pen", 5);
    Product penlag = pen2--;
    
    cout << 4 << 5 << endl;
    cout << pen2.toString() << endl;
    cout << penlag.toString() << endl;

    Product empty("empty", 1);

    cout << 1 << 0 << 0 << endl;
    cout << empty.toString() << endl;
    --empty;
    cout << empty.toString() << endl;
    --empty;
    cout << empty.toString() << endl;

    cout << endl;

    Product b("bottle", 3);
    cout << b.toString() << endl;
    cout << b << endl;
}
