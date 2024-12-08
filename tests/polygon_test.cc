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
  EXPECT_TRUE(is_convex_polygon({{0, 0}, {1, 0}})) << "-";
  EXPECT_TRUE(is_convex_polygon({{0, 0}, {0, 1}})) << "|";
  EXPECT_FALSE(is_convex_polygon({{1, 2}, {1, 2}})) << "p0 == p1";

  EXPECT_FALSE(is_convex_polygon({{0, 0}, {0, 0}, {0, 0}})) << "p0 == p1 == p2";
  EXPECT_FALSE(is_convex_polygon({{0, 0}, {1, 1}, {0, 0}})) << "p0 == p2";
  EXPECT_FALSE(is_convex_polygon({{2, 1}, {0, 2}, {0, 2}})) << "p1 == p2";
  EXPECT_TRUE(is_convex_polygon({{0, 0}, {1, 0}, {1, 1}})) << "◺ ↺";
  EXPECT_TRUE(is_convex_polygon({{0, 0}, {1, 1}, {1, 0}})) << "◺ ↻";

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
  EXPECT_TRUE(is_convex_loose({{0, 0}, {1, 0}})) << "-";
  EXPECT_TRUE(is_convex_loose({{0, 0}, {0, 1}})) << "|";
  EXPECT_TRUE(is_convex_loose({{1, 2}, {1, 2}})) << "p0 == p1";

  EXPECT_TRUE(is_convex_loose({{0, 0}, {0, 0}, {0, 0}})) << "p0 == p1 == p2";
  EXPECT_TRUE(is_convex_loose({{0, 0}, {1, 1}, {0, 0}})) << "p0 == p2";
  EXPECT_TRUE(is_convex_loose({{2, 1}, {0, 2}, {0, 2}})) << "p1 == p2";
  EXPECT_TRUE(is_convex_loose({{0, 0}, {1, 0}, {1, 1}})) << "◺ ↺";
  EXPECT_TRUE(is_convex_loose({{0, 0}, {1, 1}, {1, 0}})) << "◺ ↻";

  EXPECT_TRUE(is_convex_loose({{0, 0}, {1, 0}, {1, 1}, {0, 1}})) << "□ ↺";
  EXPECT_TRUE(is_convex_loose({{0, 0}, {0, 1}, {1, 1}, {1, 0}})) << "□ ↻";
  EXPECT_FALSE(is_convex_loose({{0, 0}, {1, 1}, {0, 2}, {2, 1}})) << "➤";
  EXPECT_FALSE(is_convex_loose({{0, 0}, {1, 1}, {0, 1}, {1, 0}})) << "⧖";

  EXPECT_FALSE(is_convex_loose({{1, 0}, {4, 2}, {0, 2}, {3, 0}, {2, 3}}))
      << "⚝ (self-intersecting polygon with only convex angles)";
}

std::string draw_polygon(std::vector<Point>& poly, int margin = 0) {
  const auto& xmm = std::minmax_element(
      poly.begin(), poly.end(), [](auto& p1, auto& p2) { return p1.x < p2.x; });
  const auto& ymm = std::minmax_element(
      poly.begin(), poly.end(), [](auto& p1, auto& p2) { return p1.y < p2.y; });
  int32_t xmin = xmm.first->x - margin;
  int32_t xmax = xmm.second->x + margin;
  int32_t ymin = ymm.first->y - margin;
  int32_t ymax = ymm.second->y + margin;

  const char* alphabet = " O.";
  char plot[(ymax - ymin + 1) * (xmax - xmin + 2) + 1];
  char* p = plot;
  for (int y = ymax; y >= ymin; y--) {
    for (int x = xmin; x <= xmax; x++) {
      int rel = point_polygon_relationship(Point(x, y), poly);
      *(p++) = alphabet[rel + 1];
    }
    *(p++) = '\n';
  }
  *p = 0;
  return plot;
}

TEST(PointPolygonRelationship, Works) {
  std::vector<Point> square = {{0, 0}, {0, 2}, {2, 2}, {2, 0}};
  std::string square_plot =
      "     \n"
      " OOO \n"
      " O.O \n"
      " OOO \n"
      "     \n";
  EXPECT_EQ(square_plot, draw_polygon(square, 1));

  std::vector<Point> diamond = {{2, 0}, {4, 2}, {2, 4}, {0, 2}};
  std::string diamond_plot =
      "       \n"
      "   O   \n"
      "  O.O  \n"
      " O...O \n"
      "  O.O  \n"
      "   O   \n"
      "       \n";
  EXPECT_EQ(diamond_plot, draw_polygon(diamond, 1));

  std::vector<Point> hourglass = {{0, 0}, {0, 4}, {4, 0}, {4, 4}};
  std::string hourglass_plot =
      "O   O\n"
      "OO OO\n"
      "O.O.O\n"
      "OO OO\n"
      "O   O\n";
  EXPECT_EQ(hourglass_plot, draw_polygon(hourglass));

  std::vector<Point> barbell = {{2, 2}, {0, 0}, {0, 4}, {2, 2},
                                {6, 2}, {8, 4}, {8, 0}, {6, 2}};
  std::string barbell_plot =
      "O       O\n"
      "OO     OO\n"
      "O.OOOOO.O\n"
      "OO     OO\n"
      "O       O\n";
  EXPECT_EQ(barbell_plot, draw_polygon(barbell));

  std::vector<Point> hollow_star = {{0, 8}, {16, 8}, {4, 0}, {8, 12}, {12, 0}};
  std::string hollow_star_plot =
      "        O        \n"
      "        .        \n"
      "        .        \n"
      "       O.O       \n"
      "OOOOOOOOOOOOOOOOO\n"
      "  .....   .....  \n"
      "   O..O   O..O   \n"
      "     .     .     \n"
      "      O   O      \n"
      "     O.. ..O     \n"
      "     ..O O..     \n"
      "     .     .     \n"
      "    O       O    \n";
  EXPECT_EQ(hollow_star_plot, draw_polygon(hollow_star));
}

}  // namespace
