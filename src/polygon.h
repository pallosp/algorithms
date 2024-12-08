#pragma once

#include "point.h"

// Computes the orientation of three points on the Euclidean plane.
//  +1 if they are are in anticlockwise order;
//  0 if they are collinear;
//  -1 if they are in clockwise order.
int triangle_orientation(const Point& a, const Point& b, const Point& c);

// Tells whether the polygon is convex. If strict=false, allows 180º angles and
// coincident points.
bool is_convex_polygon(const std::vector<Point>& vertices, bool strict = true);

// -1 if the point is outside the polygon;
// 0 if it's on the perimeter;
// 1 if it's inside.
// Points inside the holes of self-intersecting polygons are considered to be
// outside.
int point_polygon_relationship(const Point& point,
                               const std::vector<Point>& vertices);
