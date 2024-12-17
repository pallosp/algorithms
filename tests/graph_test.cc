#include "../src/graph.h"

#include <gtest/gtest.h>

#include <cmath>
#include <utility>
#include <vector>

namespace {

using testing::PrintToString;

TEST(GraphMatrixToEdges, Works) {
  std::vector<std::vector<double>> graph = {{0, -1}, {INFINITY, 2}};
  std::vector<std::vector<std::pair<double, int>>> expected = {
      {{0, 0}, {-1, 1}}, {{2, 1}}};
  EXPECT_EQ(graph_matrix_to_edges(graph), expected);
}

TEST(ShortestPaths, DenseGraph_OneNode) {
  std::vector<std::vector<double>> graph({{0}});
  std::vector<std::pair<double, int>> expected = {{0, -1}};
  EXPECT_EQ(shortest_paths(graph, 0), expected);
}

TEST(ShortestPaths, SparseGraph_OneNode) {
  std::vector<std::vector<std::pair<double, int>>> graph({{}});
  std::vector<std::pair<double, int>> expected = {{0, -1}};
  EXPECT_EQ(shortest_paths(graph, 0), expected);
}

TEST(ShortestPaths, DenseGraph_TwoNodesWithLoopEdge) {
  std::vector<std::vector<double>> graph({{1, 2}, {3, 0}});

  std::vector<std::pair<double, int>> expected = {{0, -1}, {2, 0}};
  EXPECT_EQ(shortest_paths(graph, 0), expected);

  expected = {{3, 1}, {0, -1}};
  EXPECT_EQ(shortest_paths(graph, 1), expected);
}

TEST(ShortestPaths, SparseGraph_TwoNodesWithLoopEdge) {
  std::vector<std::vector<std::pair<double, int>>> graph({
      {{1, 0}, {2, 1}},
      {{3, 0}},
  });

  std::vector<std::pair<double, int>> expected = {{0, -1}, {2, 0}};
  EXPECT_EQ(shortest_paths(graph, 0), expected);

  expected = {{3, 1}, {0, -1}};
  EXPECT_EQ(shortest_paths(graph, 1), expected);
}

TEST(ShortestPaths, DenseGraph_DisconnectedNodes) {
  double inf = INFINITY;
  std::vector<std::vector<double>> graph(
      {{0, inf, inf}, {inf, 0, inf}, {inf, inf, 0}});
  std::vector<std::pair<double, int>> expected = {
      {inf, -1}, {0, -1}, {inf, -1}};
  EXPECT_EQ(shortest_paths(graph, 1), expected);
}

TEST(ShortestPaths, SparseGraph_DisconnectedNodes) {
  double inf = INFINITY;
  std::vector<std::vector<std::pair<double, int>>> graph({{}, {}, {}});
  std::vector<std::pair<double, int>> expected = {
      {inf, -1}, {0, -1}, {inf, -1}};
  EXPECT_EQ(shortest_paths(graph, 1), expected);
}

TEST(ShortestPaths, DenseGraph_FiveNodes) {
  double inf = INFINITY;
  std::vector<std::vector<double>> graph({{0, 10, inf, 3, inf},
                                          {inf, 0, 1, 2, inf},
                                          {inf, inf, 0, inf, 4},
                                          {inf, 3, 9, 0, 2},
                                          {7, inf, 6, inf, 0}});
  std::vector<std::pair<double, int>> paths = shortest_paths(graph, 0);
  std::vector<std::pair<double, int>> expected = {
      {0, -1}, {6, 3}, {7, 1}, {3, 0}, {5, 3}};
  EXPECT_EQ(paths, expected);
}

TEST(ShortestPaths, SparseGraph_FiveNodes) {
  std::vector<std::vector<std::pair<double, int>>> graph({
      {{10, 1}, {3, 3}},
      {{1, 2}, {2, 3}},
      {{4, 4}},
      {{3, 1}, {9, 2}, {2, 4}},
      {{7, 0}, {6, 2}},
  });
  std::vector<std::pair<double, int>> expected = {
      {0, -1}, {6, 3}, {7, 1}, {3, 0}, {5, 3}};
  EXPECT_EQ(shortest_paths(graph, 0), expected);
}

TEST(ShortestPaths, Randomized_AlgorithmsAreEquivalent) {
  int n = 5;
  for (int a = 0; a < 10; a++) {
    // Generate a random graph and choose a random root node.
    std::vector<std::vector<double>> graph;
    for (int i = 0; i < n; i++) {
      std::vector<double> row;
      for (int j = 0; j < n; j++) {
        int r = rand() % 5;
        row.push_back(r == 0 ? INFINITY : r - 1);
      }
      graph.push_back(row);
    }
    auto edges = graph_matrix_to_edges(graph);
    int root = rand() % n;

    std::vector<double> distances1, distances2;
    for (auto& p : shortest_paths(graph, root)) distances1.push_back(p.first);
    for (auto& p : shortest_paths(edges, root)) distances2.push_back(p.first);

    ASSERT_EQ(distances1, distances2) << PrintToString(graph);
  }
}

}  // namespace
