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
  // `less`: upward edge, `greater`: downward edge
  auto last_edge_dy = std::strong_ordering::equal;
  // number switches from upward to downward edges or vice versa
  int edge_dy_switches = 0;

  for (const Point& v : vertices) {
    int o = triangle_orientation(v0, v1, v);
    if (o == 0) {
      if (strict) return false;
    } else {
      if (o + last_orientation == 0) return false;
      last_orientation = o;
    }

    auto edge_dy = v1 <=> v;
    if (edge_dy != 0) {
      edge_dy_switches += last_edge_dy != 0 && last_edge_dy != edge_dy;
      last_edge_dy = edge_dy;
    }

    v0 = v1;
    v1 = v;
  }
  return edge_dy_switches <= 2;
}

int point_polygon_relationship(const Point& p,
                               const std::vector<Point>& vertices) {
  if (vertices.empty()) return -1;

  Point last = vertices.back();
  int x = p.x;
  int y = p.y;
  int left_edges = 0;  // number of edges to the left of p

  for (const Point& v : vertices) {
    if (p == v) return 0;
    const Point& bottom = last.y <= v.y ? last : v;
    const Point& top = last.y <= v.y ? v : last;
    if (y >= bottom.y && y < top.y) {
      int c = triangle_orientation(p, bottom, top);
      if (c == 0) return 0;
      if (c > 0) left_edges++;
    } else if (y == bottom.y && y == top.y) {
      if ((x > bottom.x && x < top.x) || (x > top.x && x < bottom.x)) return 0;
    }
    last = v;
  }

  return left_edges & 1 ? 1 : -1;
}
