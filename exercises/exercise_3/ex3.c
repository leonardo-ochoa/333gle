/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoa2

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Point3d.h"

// test Point3d_Allocate by comparing Point3d_Allocate to a
// struct. 3 arguments are of int32_t/
bool Test_Allocate(int32_t x_arg, int32_t y_arg, int32_t z_arg3);

// test Point3d_Allocate by comparing point_3d_ptr to a
// struct after being scaled. Arguments passed in are
// a pointer to Point3d, a Point3d and a scale value
bool Test_Scale(Point3d* point_3d_ptr, Point3d point_3d, int32_t scale);

// test that Point3d_GetOrigin was set at the origin.
bool Test_GetOrigin();

bool Test_Allocate(int32_t x_arg, int32_t y_arg, int32_t z_arg3) {
  Point3d* allocated = Point3d_Allocate(x_arg, y_arg, z_arg3);
  Point3d test_point = {x_arg, y_arg, z_arg3};
  if (allocated->x != test_point.x || allocated->y != test_point.y
     || allocated->z != test_point.z) {
    printf("values x, y, and z were not allocated correclty \n");
    free(allocated);
    return false;
  }
  free(allocated);
  return true;
}

bool Test_Scale(Point3d* point_3d_ptr, Point3d point_3d, int32_t scale) {
  Point3d_Scale(point_3d_ptr, scale);
  point_3d.x *= scale;
  point_3d.y *= scale;
  point_3d.z *= scale;
  if (point_3d_ptr->x != point_3d.x || point_3d_ptr->y != point_3d.y
     || point_3d_ptr->z != point_3d.z) {
    printf("values x, y, and z were not scaled correclty \n");
    free(point_3d_ptr);
    return false;
  }
  return true;
}

bool Test_GetOrigin() {
  Point3d get_origin = Point3d_GetOrigin();
  Point3d origin = {0, 0, 0};
  if (get_origin.x != origin.x || get_origin.y != origin.y
     || get_origin.z != origin.z) {
    printf("values x, y, and z were not set to the origin\n");
    return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  if (!Test_Allocate(1, 2, 3)) {
    exit(1);
  }

  Point3d* allocate = Point3d_Allocate(7, 8, 9);
  Point3d point = {7, 8, 9};
  if (!Test_Scale(allocate, point, 10)) {
    exit(1);
  }

  if (!Test_GetOrigin()) {
    exit(1);
  }
  free(allocate);
  exit(0);
}
