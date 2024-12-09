#pragma once

#include <vector>

#include "point.h"

// Returns the minimal subset of points that span the convex hull.
std::vector<Point> convex_hull(const std::vector<Point> &points);
