#include "convex_hull.h"

#include <algorithm>
#include <vector>

#include "point.h"
#include "polygon.h"

namespace {

// Sorts the points in-place. The first one will be the leftmost one of the
// bottom-most points. The rest are sorted lexicographically by arg(p₀->pᵢ) then
// by -|pᵢ-p₀|.
void sort_by_angle(std::vector<Point> &p) {
  auto bottom_left_it = std::min_element(p.begin(), p.end());
  std::swap(*p.begin(), *bottom_left_it);
  std::sort(p.begin() + 1, p.end(), [&p](auto &q, auto &r) {
    int o = triangle_orientation(p[0], q, r);
    return o > 0 || (o == 0 && q >= r);
  });
}

}  // namespace

std::vector<Point> convex_hull(const std::vector<Point> &points) {
  unsigned i, n = points.size();
  if (n <= 1) return points;
  std::vector<Point> p = points;
  sort_by_angle(p);

  // Prune the middle and the duplicate points from the hull's last edge.
  while (n > 2 && triangle_orientation(p[0], p[n - 1], p[n - 2]) == 0) n--;
  if (p[0] == p[n - 1]) n--;

  // First two points of the hull.
  std::vector<Point> hull(p.begin(), p.begin() + std::min(n, 2u));

  // Special case: all points are collinear.
  if (n <= 2) return hull;

  // Skip the points between p[0] and p[1].
  i = 2;
  while (triangle_orientation(p[0], p[1], p[i]) == 0) i++;

  // Build the rest of the hull.
  while (i < n) {
    while (triangle_orientation(hull[hull.size() - 2], hull.back(), p[i]) <= 0)
      hull.pop_back();
    hull.push_back(p[i++]);
  }

  return hull;
}
