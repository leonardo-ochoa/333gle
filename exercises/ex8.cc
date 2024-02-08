/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoa2@uw.edu
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string.h>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ifstream;
using std::string;
using std::map;
// reads a token from the input stream "in"
// stores parsed token T and stores it in output
// if successful return true otherwise false
template <typename T> bool ReadValue(ifstream& in, T* const output);

int main(int argc, char** argv) {
  if (argc != 2) {
    cerr << "Usage: ./ex7 <file>" << endl;
    return EXIT_FAILURE;
  }
  ifstream instream(argv[1]);
  string val;
  map<string, int> map_string;
  if (instream.is_open()) {
    while (ReadValue<string>(instream, &val)) {
        map_string[val]++;
    }
    if (!instream.eof()) {
      cerr << "bad input" << endl;
      return EXIT_FAILURE;
    }
    instream.close();
  } else {
    cerr << "error opening " << argv[1] << endl;
    return EXIT_FAILURE;
  }
  for (auto& word : map_string) {
    cout << word.first << " " << word.second << endl;
  }
  return EXIT_SUCCESS;
}

template <typename T> bool ReadValue(ifstream& in, T* const output) {
  in >> *output;
  if (in.fail()) {
    return false;
  } else {
    return true;
  }
}
