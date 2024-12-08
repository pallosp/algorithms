#pragma once

#include <ostream>

// Point on the Euclidean plane.
struct Point {
  int x;
  int y;

  Point(int x, int y) {
    this->x = x;
    this->y = y;
  }

  bool operator==(const Point &p) const { return x == p.x && y == p.y; }

  // Compares two points lexicographically, first by their y-coordinates then
  // their x-coordinates.
  auto operator<=>(const Point &p) const {
    auto dy = y <=> p.y;
    return dy == 0 ? x <=> p.x : dy;
  }

  friend std::ostream &operator<<(std::ostream &stream, const Point &point) {
    return stream << "(" << point.x << "," << point.y << ")";
  }
};
