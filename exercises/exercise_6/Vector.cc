/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoa2@uw.edu
#include <cstdlib>
#include "Vector.h"

Vector::Vector() : x_(0), y_(0), z_(0) {}

Vector::Vector(const float x, const float y, const float z)
                : x_(x), y_(y), z_(z) {}

Vector::Vector(const Vector& copy) : x_(copy.x_), y_(copy.y_), z_(copy.z_) {}

Vector::~Vector() {}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
      x_ = other.x_;
      y_ = other.y_;
      z_ = other.z_;
    }
    return *this;
}

Vector& Vector::operator+=(const Vector& other) {
    x_ += other.x_;
    y_ += other.y_;
    z_ += other.z_;
    return *this;
}

Vector& Vector::operator-=(const Vector& other) {
    x_ -= other.x_;
    y_ -= other.y_;
    z_ -= other.z_;
    return *this;
}

float Vector::operator*(const Vector& other) const {
  float product = x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
  return product;
}
