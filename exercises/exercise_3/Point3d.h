/*
 * Copyright ©2023 Leonardo Ochoa
 */
#include <stdint.h>

#ifndef POINT3D_H_
#define POINT3D_H_

// a 3 dimensional point
typedef struct point3d_st {
  int32_t x; // x value of a point
  int32_t y; // y value of a point
  int32_t z; // z value of a point
} Point3d;

// Funtcion takes 3 arguments for x, y, and z. it Assigns those three
// arguments to some Point3d struct and return the pointer of the struct
// If it could not allocate memory it returns a failure.
// arguments must be of type int32_t otherwise there will
// be unexpected behavior
Point3d* Point3d_Allocate(int32_t x_arg, int32_t y_arg, int32_t z_arg3);

// Function taked in a pointer to some Point3d struct and a scalar value.
// scales x, y and z fields by the scalar value.
// scale must be of type int32_t otherwise there will
// be unexpected behavior
void Point3d_Scale(Point3d* point_3d, int32_t scale);

// Returns a Point3d struct whose origin is set to zeros
Point3d Point3d_GetOrigin();

#endif // POINT3D_H_
