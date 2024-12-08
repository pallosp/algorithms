#include "polygon.h"

#include "point.h"

namespace {

int sign(int64_t x) { return (x > 0) - (x < 0); }

}  // namespace

int triangle_orientation(const Point& a, const Point& b, const Point& c) {
  return sign((int64_t)(b.x - a.x) * (c.y - a.y) -
              (int64_t)(b.y - a.y) * (c.x - a.x));
}

bool is_convex_polygon(const std::vector<Point>& vertices, bool strict) {
  size_t n = vertices.size();
  if (n <= 1) return true;
  if (n == 2) return !strict || vertices[0] != vertices[1];

  Point v0 = vertices[n - 2];
  Point v1 = vertices[n - 1];
  int last_orientation = 0;
  // Negative if 0 ≤ arg(v0→v1) < 180º; 0 if v0 == v1; positive otherwise
  auto last_angle = v0 <=> v1;
  // The actual sum is 180º times this value.
  int exterior_angle_sum = 0;

  for (const Point& v : vertices) {
    int o = triangle_orientation(v0, v1, v);
    if (o == 0) {
      if (strict) return false;
    } else {
      if (o + last_orientation == 0) return false;
      last_orientation = o;
    }

    auto angle = v1 <=> v;
    if (angle != 0) {
      exterior_angle_sum += last_angle != 0 && last_angle != angle;
      last_angle = angle;
    }

    v0 = v1;
    v1 = v;
  }

  return exterior_angle_sum == 2;
}
