/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoa2@uw.edu
#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

namespace vector333 {

// constructs a 3-D vector
class Vector {
 public:
  // default constructor
  Vector();
  // constructor that takes in 3 arguments
  Vector(const float x, const float y, const float z);
  // copies the conent from the given Vector into this
  Vector(const Vector& copy);
  // Deconstructs the vector
  ~Vector();
  // sets the components of this equal to other
  Vector& operator=(const Vector& other);
  // adds the components of other to this
  Vector& operator+=(const Vector& other);
  // subtracts the components of other to this
  Vector& operator-=(const Vector& other);
  // computes inner product of other and this and
  // returns it as a float
  float operator*(const Vector& other) const;
  // returns a new vector whose components are the components
  // of v multiplied by k
  friend Vector operator*(const Vector& v, const float k);
  // returns a new vector whose components are the components
  // of v multiplied by k
  friend Vector operator*(const float k, const Vector& v);
  // returns a stream that prints out the given vector
  friend std::ostream& operator<<(std::ostream& out, const Vector& v);

 private:
  float* magnitude_;
};

// returns a new vector whose components are the components
// of v1 plus the components of v2
Vector operator+(const Vector& v1, const Vector& v2);
// returns a new vector whose components are the components
// of v1 minus the components of v2
Vector operator-(const Vector& v1, const Vector& v2);


}  // namespace vector333

#endif  // VECTOR_H_
