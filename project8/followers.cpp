// followers.cpp
// Jake Herrmann
// 03 Dec 2018
//
// CS 311 Fall 2018
// Source for following-words program


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

#include <sys/stat.h>


// following-words set type
// The set of following words associated with some word.
using SetType = set<string>;

// following-words map type
// A map where each key-value pair is a unique word and its associated set of
// following words.
using MapType = map<string, SetType>;


// make_word_map
// Populate the given following-words map for the given file. Print an error
// message and exit if there is an error reading the file.
void make_word_map(const string & path, MapType & wordmap)
{
    string current_word;
    string next_word;
    ifstream file;

    file.open(path);
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
	// This is sufficient to handle the majority of error conditions,
	// including empty or blank user input, names of files that don't
	// exist, and files without read permissions.
	cout << "Error reading file '" << path << "'" << endl;
	exit(1);
    }
}


// print_stats
// Print statistics for the given following-words map.
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


// is_dir
// Return true if the given path specifies a directory and false otherwise.
//
// adapted from:
// http://forum.codecall.net/topic/68935-how-to-test-if-file-or-directory/?p=624747
bool is_dir(const string & path) {
    struct stat buf;
    stat(path.c_str(), &buf);
    return S_ISDIR(buf.st_mode);
}


// main
// Read a file path from user input. If the path is a directory, print an error
// message and exit. Otherwise, print the file's following-words statistics.
int main()
{
    string path;
    MapType wordmap;

    cout << "Enter a path to a file: ";
    getline(cin, path);

    if (is_dir(path)) {
	// This error condition won't be detected by make_word_map so we must
	// check for it here.
	cout << "'" << path << "' is a directory" << endl;
	exit(1);
    }

    make_word_map(path, wordmap);
    print_stats(wordmap);

    return 0;
}
