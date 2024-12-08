#include "polygon.h"

#include "point.h"

namespace {

int sign(int64_t x) { return (x > 0) - (x < 0); }

}  // namespace

int triangle_orientation(const Point& a, const Point& b, const Point& c) {
  return sign((int64_t)(b.x - a.x) * (c.y - a.y) -
              (int64_t)(b.y - a.y) * (c.x - a.x));
}
