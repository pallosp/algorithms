#include "../src/convex_hull.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../src/point.h"
#include "../src/polygon.h"

namespace {

using testing::ElementsAre;
using testing::IsEmpty;
using testing::PrintToString;

typedef Point P;

TEST(ConvexHull, Works) {
  // 0 points
  EXPECT_THAT(convex_hull({}), IsEmpty());
  // 1 point
  EXPECT_THAT(convex_hull({{1, 2}}), ElementsAre<Point>(P(1, 2)));
  // Coincident points, should dedupe
  EXPECT_THAT(convex_hull({{1, 2}, {1, 2}}), ElementsAre(P(1, 2)));
  // Square, should lexicographically sort
  EXPECT_THAT(convex_hull({{1, 1}, {1, 0}, {0, 1}, {0, 0}}),
              ElementsAre(P(0, 0), P(1, 0), P(1, 1), P(0, 1)));
  // Horizontal line, should sort by x-coordinate
  EXPECT_THAT(convex_hull({{1, 0}, {0, 0}, {2, 0}}),
              ElementsAre(P(0, 0), P(2, 0)));
  // Horizontal line with duplicate points
  EXPECT_THAT(convex_hull({{0, 0}, {1, 0}, {2, 0}, {0, 0}, {2, 0}}),
              ElementsAre(P(0, 0), P(2, 0)));
  // Square and its center
  EXPECT_THAT(convex_hull({{0, 0}, {0, 2}, {2, 0}, {2, 2}, {1, 1}}),
              ElementsAre(P(0, 0), P(2, 0), P(2, 2), P(0, 2)));
  // 3x3 grid
  std::vector<Point> grid = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1},
                             {1, 2}, {2, 0}, {2, 1}, {2, 2}};
  EXPECT_THAT(convex_hull(grid),
              ElementsAre(P(0, 0), P(2, 0), P(2, 2), P(0, 2)));
}

TEST(ConvexHull, Randomized) {
  for (int i = 0; i < 100; i++) {
    std::vector<Point> points;
    for (int j = 0; j < 8; j++) points.emplace_back(rand() % 4, rand() % 4);
    const std::vector<Point> hull = convex_hull(points);

    // The convex hull must be strictly convex.
    ASSERT_TRUE(is_convex_polygon(hull, true)) << PrintToString(hull);

    // Each point must be inside or on the convex hull.
    for (const Point& p : points) {
      ASSERT_GE(point_polygon_relationship(p, hull), 0);
    }
  }
}

}  // namespace
