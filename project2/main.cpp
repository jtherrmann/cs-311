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
}
