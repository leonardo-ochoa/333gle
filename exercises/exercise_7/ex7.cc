/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoaTWO@uw.edu
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Vector.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using vector333::Vector;
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4

// tests the default constructor, constructor, and copy constructor
void TestOut();
// test for nonmemeber plus
void TestPlus();
// test for nonmemeber minus
void TestMinus();
// test value * product
void TestKV();
// test product * value
void TestVK();
// test member operators
void TestMembers();

void PrintResult(string test, string expected, Vector v);

int main(int argc, char** argv) {
  TestOut();
  TestPlus();
  TestMinus();
  TestKV();
  TestVK();
  TestMembers();
  return EXIT_SUCCESS;
}

void TestOut() {
  Vector v1;
  PrintResult("default constructor", "(0,0,0)", v1);
  Vector v2(ONE, TWO, THREE);
  PrintResult("constructor", "(1,2,3)", v2);
  Vector v3(v2);
  PrintResult("copy constructor", "(1,2,3)", v3);
}

void TestPlus() {
  Vector v1(ONE, TWO, THREE);
  Vector v2(ONE, TWO, THREE);
  Vector v3 = v1 + v2;
  PrintResult("v1 + v2", "(2,4,6)", v3);
}

void TestMinus() {
  Vector v1(ONE, TWO, THREE);
  Vector v2(ONE, TWO, THREE);
  Vector v3 = v1 - v2;
  PrintResult("v1 - v2", "(0,0,0)", v3);
}

void TestKV() {
  Vector v1(ONE, TWO, THREE);
  float scale = FOUR;
  Vector v2 = scale * v1;
  PrintResult("k * v", "(4,8,12)", v2);
}

void TestVK() {
  Vector v1(ONE, TWO, THREE);
  float scale = FOUR;
  Vector v2 = v1 * scale;
  PrintResult("v * k", "(4,8,12)", v2);
}

void TestMembers() {
  Vector v1(ONE, TWO, THREE);
  Vector v2(THREE, TWO, ONE);
  v1 += v2;
  PrintResult("v1 += v2", "(4,4,4)", v1);
  v1 -= v2;
  PrintResult("v1 -= v2", "(1,2,3)", v1);
  float product = v1 * v2;
  cout << "Testing v1 * v2: "<< endl;
  cout << "Expected: 10" << endl;
  cout << "Actual: " << product << endl;
}

void PrintResult(string test, string expected, Vector v) {
  cout << "Testing " << test << ": "<< endl;
  cout << "Expected: " << expected << endl;
  cout << "Actual: ";
  cout << v << endl << endl;
}
