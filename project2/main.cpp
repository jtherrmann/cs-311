#include <utility>
using std::move;

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include "ssarray.h"

int main() {
    SSArray<int> a;
    a[1] = 2;
    for (int i = 0; i < a.size(); i++)
	cout << i << ": " << a[i] << endl;

    cout << endl;

    SSArray<char> carr(3);
    carr[1] = 'a';
    for (int i = 0; i < carr.size(); i++)
	cout << i << ": " << carr[i] << endl;

    cout << endl;

    SSArray<int> iarr(5);
    iarr[4] = 1;
    // cout << *(iarr.begin()) << endl;
    // cout << *(iarr.end() - 1) << endl;
    // cout << *(iarr.end()) << endl;
    for (auto x : iarr)
	cout << x << endl;
    // cout << *(it+1) << endl;
    // cout << it << endl;

    // cout << endl;

    // vector<int> v {0, 1, 2, 3, 4};
    // cout << *(begin(v)+1) << endl;
    // cout << *(v.begin()) << endl;

    cout << endl;

    cout << "< test:" << endl;

    SSArray<int> a1;
    a1[2] = 3;

    SSArray<int> a2;

    cout << 1 << endl;
    cout << (a1 > a2) << endl;

    // cout << 0 << endl;
    // cout << (a1 == a2) << endl;

    // a2[2] = 3;
    // cout << 1 << endl;
    // cout << (a1 == a2) << endl;

    cout << endl;

    SSArray<int> mut;
    // mut[0] = 3;
    auto it = mut.begin();
    *it = 3;
    cout << mut[0] << endl;

    const SSArray<int> immut;
    // immut[0] = 3;
    auto it2 = immut.begin();
    cout << it2 << endl;
    // *it2 = 3;
    cout << immut[0] << endl;

    cout << endl;

    cout << "test copy ctor:" << endl << endl;

    SSArray<int> orig;
    for(int i = 0; i < orig.size(); ++i) {
	orig[i] = i;
    }

    SSArray<int> copy(orig);

    for(auto x : orig)
	cout << x << endl;

    cout << endl;

    for(auto x : copy)
	cout << x << endl;

    cout << endl;

    cout << 1 << endl;
    cout << (orig == copy) << endl;

    cout << endl;

    cout << "test move ctor:" << endl << endl;
    SSArray<int> movable(3);
    SSArray<int> moved(move(movable));
    movable.~SSArray();
    for(auto x : moved)
    	cout << x << endl;
    // for(auto x : movable)
    // 	cout << x << endl;

    // SSArray<int> test;
    // cout << test.begin() << endl;
    // cout << *test.begin() << endl;
    // test.begin() = nullptr;
    // cout << test.begin() << endl;
    // cout << *test.begin() << endl;

    cout << endl;

    cout << "test copy assign:" << endl << endl;

    SSArray<int> first(4);
    first[0] = 2;
    SSArray<int> second;
    second = first;
    first[0] = 1;
    for(auto x : first)
	cout << x << endl;
    cout << endl;
    for(auto x : second)
	cout << x << endl;
    // cout << (first == second) << endl;

    cout << endl;

    cout << "test move assign:" << endl << endl;

    SSArray<int> foo(4);
    SSArray<int> bar;
    bar = move(foo);
    for(auto x : foo)
	cout << x << endl;
    cout << endl;
    for(auto x : bar)
	cout << x << endl;

    return 0;
}
