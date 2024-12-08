#include "../src/polygon.h"

#include <gtest/gtest.h>

#include "../src/point.h"

namespace {

TEST(TriangleOrientation, Works) {
  EXPECT_EQ(-1, triangle_orientation({1, 1}, {3, 2}, {7, 3}));
  EXPECT_EQ(0, triangle_orientation({1, 1}, {3, 2}, {7, 4}));
  EXPECT_EQ(1, triangle_orientation({1, 1}, {3, 2}, {7, 5}));
  EXPECT_EQ(0, triangle_orientation({0, 0}, {1, 1}, {1, 1}));
}

}  // namespace
