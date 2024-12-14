#include "../src/graph.h"

#include <gtest/gtest.h>

#include <utility>
#include <vector>

namespace {

TEST(ShortestPathsDenseGraph, OneNode) {
  std::vector<std::vector<double>> graph({{0}});
  std::vector<std::pair<double, int>> expected = {{0, -1}};
  EXPECT_EQ(shortest_paths_dense_graph(graph, 0), expected);
}

TEST(ShortestPathsDenseGraph, TwoNodesWithLoopEdge) {
  std::vector<std::vector<double>> graph({{1, 2}, {3, 0}});

  std::vector<std::pair<double, int>> expected = {{0, -1}, {2, 0}};
  EXPECT_EQ(shortest_paths_dense_graph(graph, 0), expected);

  expected = {{3, 1}, {0, -1}};
  EXPECT_EQ(shortest_paths_dense_graph(graph, 1), expected);
}

TEST(ShortestPathsDenseGraph, DisconnectedGraph) {
  double inf = INFINITY;
  std::vector<std::vector<double>> graph(
      {{0, inf, inf}, {inf, 0, inf}, {inf, inf, 0}});
  std::vector<std::pair<double, int>> expected = {
      {inf, -1}, {0, -1}, {inf, -1}};
  EXPECT_EQ(shortest_paths_dense_graph(graph, 1), expected);
}

TEST(ShortestPathsDenseGraph, FiveNodes) {
  double inf = INFINITY;
  std::vector<std::vector<double>> graph({{0, 10, inf, 3, inf},
                                          {inf, 0, 1, 2, inf},
                                          {inf, inf, 0, inf, 4},
                                          {inf, 3, 9, 0, 2},
                                          {7, inf, 6, inf, 0}});
  std::vector<std::pair<double, int>> paths =
      shortest_paths_dense_graph(graph, 0);
  std::vector<std::pair<double, int>> expected = {
      {0, -1}, {6, 3}, {7, 1}, {3, 0}, {5, 3}};
  EXPECT_EQ(paths, expected);
}

}  // namespace
