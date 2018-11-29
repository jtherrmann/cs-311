#include <fstream>
using std::ifstream;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <map>
using std::map;

#include <set>
using std::set;

#include <string>
using std:: getline;
using std::string;


// TODO:
// - address TODO in file
// - remove sources marked TODO
// - document
// - read project description & coding standards


// TODO:
// https://www.cs.uaf.edu/~chappell/class/2018_fall/cs311/lect/cs311-20181126-table_stl.pdf
// slide 26
// - use std::map from <map>
//   - because keys are unique and sorted by operator<
// - for each word, if it's not a key in the map, set it to an empty set
// - for each word, insert the word immediately after it into the first word's
//   set


using SetType = set<string>;
using MapType = map<string, SetType>;


MapType & make_word_map(const string & filename, MapType & wordmap)
{
    // TODO: source: http://www.cplusplus.com/doc/tutorial/files/
    string current_word;
    string next_word;
    ifstream file;

    file.open(filename);
    file >> next_word;
    if (file) {
	while (true) {
	    current_word = next_word;

	    if (wordmap.count(current_word) == 0)
		wordmap[current_word] = SetType();

	    file >> next_word;
	    if (!file)
		break;

	    wordmap[current_word].insert(next_word);
	}
    }
    file.close();
    if (!file.eof()) {
	cout << "Error reading file '" << filename << "'" << endl;
	exit(1);
    }
    return wordmap;
}


void print_stats(const MapType & wordmap)
{
    cout << "\nNumber of distinct words: " << wordmap.size() << "\n\n";
    for (const auto & kvpair : wordmap) {
	cout << kvpair.first << ":";
	for (const auto & word : kvpair.second)
	    cout << " " << word;
	cout << endl;
    }
}


int main()
{
    // TODO:
    // - input filename validation
    //   - trim whitespace from beginnig & end of input filename

    // TODO: source: https://en.cppreference.com/w/cpp/string/basic_string/getline

    string filename;
    MapType wordmap;

    cout << "Enter a filename: ";
    getline(cin, filename);

    make_word_map(filename, wordmap);
    print_stats(wordmap);

    return 0;
}
