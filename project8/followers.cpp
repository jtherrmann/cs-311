// followers.cpp
// Jake Herrmann
// 03 Dec 2018
//
// CS 311 Fall 2018
// Source for following-words program


#include <fstream>
using std::ifstream;

#include <ios>
using std::ios_base;

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


// following-words set type
// The set of following words associated with some word.
using SetType = set<string>;

// following-words map type
// A map where each key-value pair is a unique word and its associated set of
// following words.
using MapType = map<string, SetType>;


// make_word_map
// Given a file path and an empty following-words map, populate the map
// according to the words contained in the file. Print an error message and
// exit if there is an error reading the file.
//
// Pre:
// - wordmap has been default constructed and has not been modified since its
//   construction.
//
// Does not throw.
void make_word_map(const string & path, MapType & wordmap)
{
    string current_word;
    string next_word;
    ifstream file;

    file.open(path);
    try {
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
    }
    catch (ios_base::failure & e) {
	// This is necessary to handle the error condition in which the path
	// specifies a directory.
	cout << "Error reading file '" << path << "'\n";
	cout << "Hint: make sure '" << path << "' is not a directory." << endl;
	exit(1);
    }
    file.close();

    if (!file.eof()) {
	// This is sufficient to handle the majority of error conditions,
	// including empty or blank user input, names of files that don't
	// exist, and files without read permissions.
	cout << "Error reading file '" << path << "'\n";
	cout << "Hint: make sure '" << path << "' exists and you have ";
	cout << "permission to read it." << endl;
	exit(1);
    }
}


// print_stats
// Print statistics for the given following-words map.
//
// Does not throw.
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


// main
// Read a file path from user input and print the file's following-words
// statistics.
//
// Does not throw.
int main()
{
    string path;
    MapType wordmap;

    cout << "Enter a path to a file: ";
    getline(cin, path);

    make_word_map(path, wordmap);
    print_stats(wordmap);

    return 0;
}
