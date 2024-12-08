#include "../src/polygon.h"

#include <gtest/gtest.h>

#include <vector>

#include "../src/point.h"

namespace {

TEST(TriangleOrientation, Works) {
  EXPECT_EQ(-1, triangle_orientation({1, 1}, {3, 2}, {7, 3}));
  EXPECT_EQ(0, triangle_orientation({1, 1}, {3, 2}, {7, 4}));
  EXPECT_EQ(1, triangle_orientation({1, 1}, {3, 2}, {7, 5}));
  EXPECT_EQ(0, triangle_orientation({0, 0}, {1, 1}, {1, 1}));
}

TEST(IsConvexPolygon, Strict) {
  EXPECT_TRUE(is_convex_polygon({})) << "0 points";
  EXPECT_TRUE(is_convex_polygon({{1, 1}})) << "1 point";

  EXPECT_TRUE(is_convex_polygon({{1, 1}, {2, 2}})) << "/";
  EXPECT_FALSE(is_convex_polygon({{1, 2}, {1, 2}})) << "p0 == p1";

  EXPECT_TRUE(is_convex_polygon({{0, 0}, {1, 0}, {1, 1}})) << "◺ ↺";
  EXPECT_TRUE(is_convex_polygon({{0, 0}, {1, 1}, {1, 0}})) << "◺ ↻";
  EXPECT_FALSE(is_convex_polygon({{0, 0}, {1, 1}, {0, 0}})) << "p0 == p2";

  EXPECT_TRUE(is_convex_polygon({{0, 0}, {1, 0}, {1, 1}, {0, 1}})) << "□ ↺";
  EXPECT_TRUE(is_convex_polygon({{0, 0}, {0, 1}, {1, 1}, {1, 0}})) << "□ ↻";
  EXPECT_FALSE(is_convex_polygon({{0, 0}, {1, 1}, {0, 2}, {2, 1}})) << "➤";
  EXPECT_FALSE(is_convex_polygon({{0, 0}, {1, 1}, {0, 1}, {1, 0}})) << "⧖";

  EXPECT_FALSE(is_convex_polygon({{1, 0}, {4, 2}, {0, 2}, {3, 0}, {2, 3}}))
      << "⚝ (self-intersecting polygon with only convex angles)";
}

bool is_convex_loose(const std::vector<Point>& p) {
  return is_convex_polygon(p, false);
}

TEST(IsConvexPolygon, Loose) {
  EXPECT_TRUE(is_convex_loose({})) << "0 points";
  EXPECT_TRUE(is_convex_loose({{1, 1}})) << "1 point";

  EXPECT_TRUE(is_convex_loose({{1, 1}, {2, 2}})) << "/";
  EXPECT_TRUE(is_convex_loose({{1, 2}, {1, 2}})) << "p0 == p1";

  EXPECT_TRUE(is_convex_loose({{0, 0}, {1, 0}, {1, 1}})) << "◺ ↺";
  EXPECT_TRUE(is_convex_loose({{0, 0}, {1, 1}, {1, 0}})) << "◺ ↻";
  EXPECT_TRUE(is_convex_loose({{0, 0}, {1, 1}, {0, 0}})) << "p0 == p2";

  EXPECT_TRUE(is_convex_loose({{0, 0}, {1, 0}, {1, 1}, {0, 1}})) << "□ ↺";
  EXPECT_TRUE(is_convex_loose({{0, 0}, {0, 1}, {1, 1}, {1, 0}})) << "□ ↻";
  EXPECT_FALSE(is_convex_loose({{0, 0}, {1, 1}, {0, 2}, {2, 1}})) << "➤";
  EXPECT_FALSE(is_convex_loose({{0, 0}, {1, 1}, {0, 1}, {1, 0}})) << "⧖";

  EXPECT_FALSE(is_convex_loose({{1, 0}, {4, 2}, {0, 2}, {3, 0}, {2, 3}}))
      << "⚝ (self-intersecting polygon with only convex angles)";
}

}  // namespace
