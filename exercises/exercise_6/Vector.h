/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoa2@uw.edu
#ifndef VECTOR_H_
#define VECTOR_H_

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
  // return x value of this
  float get_x() const { return x_; }
  // return y value of this
  float get_y() const { return y_; }
  // return z value of this
  float get_z() const { return z_; }

 private:
  float x_;
  float y_;
  float z_;
};

#endif  // VECTOR_H_
