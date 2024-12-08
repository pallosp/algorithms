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

  friend std::ostream &operator<<(std::ostream &stream, const Point &point) {
    return stream << "(" << point.x << "," << point.y << ")";
  }
};
