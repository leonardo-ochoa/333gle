/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoa2

#include <stdlib.h>
#include <stdio.h>
#include "Point3d.h"

#define origin 0

Point3d* Point3d_Allocate(int32_t x_arg, int32_t y_arg, int32_t z_arg) {
  Point3d* new_point = (Point3d*) malloc(sizeof(Point3d));
  if (new_point == NULL) {
    printf("memory allocation failed");
    exit(1);
  }
  new_point->x = x_arg;
  new_point->y = y_arg;
  new_point->z = z_arg;
  return new_point;
}

void Point3d_Scale(Point3d* point_3d, int32_t scale) {
  point_3d->x *= scale;
  point_3d->y *= scale;
  point_3d->z *= scale;
}

Point3d Point3d_GetOrigin() {
  Point3d new_point = {origin, origin, origin};
  return new_point;
}

