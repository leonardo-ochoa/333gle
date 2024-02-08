/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoa2@uw.edu
#include <cstdlib>
#include "Vector.h"

#include <iostream>

namespace vector333 {

Vector::Vector() {
  magnitude_ = new float[3]{0, 0, 0};
}

Vector::Vector(const float x, const float y, const float z) {
  magnitude_ = new float[3]{x, y, z};
}

Vector::Vector(const Vector& copy) {
  magnitude_ = new float[3];
  magnitude_[0] = copy.magnitude_[0];
  magnitude_[1] = copy.magnitude_[1];
  magnitude_[2] = copy.magnitude_[2];
}

Vector::~Vector() {
  delete[] magnitude_;
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
      magnitude_[0] = other.magnitude_[0];
      magnitude_[1] = other.magnitude_[1];
      magnitude_[2] = other.magnitude_[2];
    }
    return *this;
}

Vector& Vector::operator+=(const Vector& other) {
    magnitude_[0] += other.magnitude_[0];
    magnitude_[1] += other.magnitude_[1];
    magnitude_[2] += other.magnitude_[2];
    return *this;
}

Vector& Vector::operator-=(const Vector& other) {
    magnitude_[0] -= other.magnitude_[0];
    magnitude_[1] -= other.magnitude_[1];
    magnitude_[2] -= other.magnitude_[2];
    return *this;
}

float Vector::operator*(const Vector& other) const {
  float product = magnitude_[0] * other.magnitude_[0] +
                  magnitude_[1] * other.magnitude_[1] +
                  magnitude_[2] * other.magnitude_[2];
  return product;
}

Vector operator+(const Vector& v1, const Vector& v2) {
  Vector temp = v1;
  temp += v2;
  return temp;
}

Vector operator-(const Vector& v1, const Vector& v2) {
  Vector temp = v1;
  temp -= v2;
  return temp;
}

Vector operator*(const Vector& v, const float k) {
  Vector temp(v.magnitude_[0] * k, v.magnitude_[1] * k, v.magnitude_[2] * k);
  return temp;
}

Vector operator*(const float k, const Vector& v) {
  Vector temp(v.magnitude_[0] * k, v.magnitude_[1] * k, v.magnitude_[2] * k);
  return temp;
}

std::ostream& operator<<(std::ostream& out, const Vector& v) {
  out << "(" << v.magnitude_[0] << "," << v.magnitude_[1]
           << "," << v.magnitude_[2] << ")";
  return out;
}

}  // namespace vector333
