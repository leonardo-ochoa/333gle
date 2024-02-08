/*
 * Copyright ©TWO0TWOTHREE Leonardo Ochoa
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
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6

// tests a defualt constructor
// return true on success, false otherwise
bool TestDefCon();

// tests a constructor
// return true on success, false otherwise
bool TestCon();

// tests that a new object is a copy of an existing object
// return true on success, false otherwise
bool TestCopy();

// tests that a Vector is set to another vector
// return true on success, false otherwise
bool TestEquals();

// tests that a Vectors values were increased by another Vectors values
// return true on success, false otherwise
bool TestPlus();

// tests that a Vectors values were decreased by another Vectors values
// return true on success, false otherwise
bool TestMinus();

// tests the inner product of TWO vectors as a float
// return true on success, false otherwise
bool TestProduct();

// Accepts an instance of a vector
// incrment that contents of the vector by ONE
void Increment(Vector passed_vector);

// Accepts a vector reference and a void*
// returns true if vector has the same value
// as void, otherwise false
bool VerifyAddress(const Vector& passed_vector, void* v);

int main(int argc, char** argv) {
  cout << "Testing Vector:" << endl;
  if (!TestDefCon() || !TestCon() || !TestCopy() || !TestEquals()
      || !TestPlus() || ! TestMinus() || !TestProduct()) {
         cerr << "Testing Failed" << endl;
        return EXIT_FAILURE;
  }
  cout << "all tests passed" << endl;
  Vector test_incr(ONE, TWO, THREE);
  Increment(test_incr);
  if (test_incr.get_x() != ONE || test_incr.get_y() != TWO
      || test_incr.get_z() != THREE) {
    cout << "Vector: pass-by-refrence" << endl;
  } else {
    cout << "Vector: pass-by-value" << endl;
  }
  if (VerifyAddress(test_incr, &test_incr)) {
    cout << "Ref: same address" << endl;
  } else {
    cout << "Ref: different address" << endl;
  }
  return EXIT_SUCCESS;
}

bool TestDefCon(void) {
  Vector v1;
  if (v1.get_x() != 0 || v1.get_y() != 0 || v1.get_z() != 0) {
    cerr << "default construcor is not set up correclty" << endl;
    return false;
  }
  return true;
}

bool TestCon(void) {
  Vector v1(ONE, TWO, THREE);
  if (v1.get_x() != ONE || v1.get_y() != TWO || v1.get_z() != THREE) {
    cerr << "default construcor is not set up correclty" << endl;
    return false;
  }
  return true;
}

bool TestCopy(void) {
  Vector v1;
  Vector v2(v1);
  if (v1.get_x() != v2.get_x() || v1.get_y() != v2.get_y()
      || v1.get_z() !=  v2.get_z()) {
    cerr << "default construcor copy is not set up correclty" << endl;
    return false;
  }
  Vector v3(ONE, TWO, THREE);
  Vector v4(v3);
  if (v3.get_x() != v4.get_x() || v3.get_y() != v4.get_y()
      || v3.get_z() !=  v4.get_z()) {
    cerr << "construcor copy is not set up correclty" << endl;
    return false;
  }
  return true;
}

bool TestEquals(void) {
  Vector v1(ONE, TWO, THREE);
  Vector v2(FOUR, FIVE, SIX);
  v1 = v2;
  if (v1.get_x() != v2.get_x() || v1.get_y() != v2.get_y()
      || v1.get_z() !=  v2.get_z()) {
    cerr << "equals assignment not working" << endl;
    return false;
  }
  return true;
}

bool TestPlus(void) {
  Vector v1(ONE, TWO, THREE);
  Vector v2(FOUR, FIVE, SIX);
  v1 += v2;
  if (v1.get_x() != FIVE || v1.get_y() != 7 || v1.get_z() !=  9) {
    cerr << "plus assignment not working" << endl;
    return false;
  }
  return true;
}

bool TestMinus(void) {
  Vector v1(ONE, TWO, THREE);
  Vector v2(FOUR, FIVE, SIX);
  v2 -= v1;
  if (v2.get_x() != THREE || v2.get_y() != THREE || v2.get_z() !=  THREE) {
    cerr << "minus assignment not working" << endl;
    return false;
  }
  return true;
}

bool TestProduct(void) {
  Vector v1(ONE, TWO, THREE);
  Vector v2(FOUR, FIVE, SIX);
  float product = v2 * v1;
  if (product != 32) {
    cerr << "product assignment not working" << endl;
    return false;
  }
  return true;
}

void Increment(Vector passed_vector) {
  Vector incr(ONE, ONE, ONE);
  passed_vector += incr;
}

bool VerifyAddress(const Vector& passed_vector, void* v) {
  return &passed_vector == v;
}
