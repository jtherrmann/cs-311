#include <fstream>
using std::ifstream;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std:: getline;
using std::string;


// TODO:
// - address TODO in file
// - remove sources marked TODO


int main()
{
    // TODO:
    // - input filename validation
    //   - trim whitespace from beginnig & end of input filename

    // TODO: source: https://en.cppreference.com/w/cpp/string/basic_string/getline
    string filename;
    cout << "Enter a filename: ";
    getline(cin, filename);

    int total = 0; // TODO temp
    string word;
    ifstream file;
    file.open(filename);
    while (true) {
	file >> word;
	if (!file)
	    break;
	++total;
	cout << word << " ";  // TODO temp
    }
    file.close();
    if (!file.eof())
	cout << "Error reading file '" << filename << "'" << endl;
    else
	// TODO: temp
	cout << total << endl;

    return 0;
}
