#pragma once

#include "point.h"

// Computes the orientation of three points on the Euclidean plane.
//  +1 if they are are in anticlockwise order;
//  0 if they are collinear;
//  -1 if they are in clockwise order.
int triangle_orientation(const Point& a, const Point& b, const Point& c);
