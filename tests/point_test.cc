#include "../src/point.h"

#include <gtest/gtest.h>

namespace {

TEST(PointComparison, Equality) {
  EXPECT_EQ(Point(1, 2), Point(1, 2));
  EXPECT_NE(Point(1, 1), Point(1, 2));
  EXPECT_NE(Point(1, 2), Point(2, 2));
}

TEST(PointComparison, Order) {
  EXPECT_LT(Point(1, 1), Point(0, 2));
  EXPECT_LT(Point(1, 1), Point(1, 2));
  EXPECT_LT(Point(1, 1), Point(2, 2));
  EXPECT_GT(Point(1, 1), Point(1, 0));
  EXPECT_LT(Point(1, 1), Point(2, 1));
  EXPECT_GT(Point(1, 1), Point(0, 0));
  EXPECT_GT(Point(1, 1), Point(1, 0));
  EXPECT_GT(Point(1, 1), Point(2, 0));

  EXPECT_LE(Point(1, 1), Point(2, 2));
  EXPECT_LE(Point(1, 1), Point(1, 1));
  EXPECT_GE(Point(1, 1), Point(1, 1));
  EXPECT_GT(Point(1, 1), Point(0, 0));
}

}  // namespace
