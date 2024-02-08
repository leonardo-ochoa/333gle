/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoa2@uw.edu

#include <iostream>
#include <cstdlib>
#include <cstring>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

// takes in the number to factorize
// and then prints its factors.
void Factor(int num);

// takes in a string returns true if the string
// is a positive integer otherwise returns false
bool CheckInteger(string val);

void Factor(int num) {
  for (int i = 1; i <= num / 2; i++) {
    if (num % i == 0) {
      cout << i << " ";
    }
  }
  cout << num << endl;
}

bool CheckInteger(string val) {
    int size = val.size();
    if (size == 0) {
      return false;
    }
    for (int i = 0; i < size; i++) {
        if (!isdigit(val[i])) {
          return false;
        }
    }
    if (stoi(val) < 1) {
      return false;
    }
    return true;
}

int main(int argc, char** argv) {
  string val;
  cout << "Which positive integer would you like me to factorize? ";
  getline(cin, val);
  if (cin) {
    // make sure input val is a positive integer (leading zeros are allowed)
    // using spaces is not allowed
    if (CheckInteger(val)) {
      Factor(stoi(val));
    } else {
      cerr << "input is not a positive integer" << endl;
      return EXIT_FAILURE;
    }
  } else {
    cerr << "there was an error with your input" << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
