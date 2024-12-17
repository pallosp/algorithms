#include "graph.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

std::vector<std::vector<std::pair<double, int>>> graph_matrix_to_edges(
    const std::vector<std::vector<double>> matrix) {
  std::vector<std::vector<std::pair<double, int>>> edges;
  for (const std::vector<double>& row : matrix) {
    std::vector<std::pair<double, int>> e;
    for (int i = 0; i < row.size(); i++) {
      if (row[i] != INFINITY) e.push_back({row[i], i});
    }
    edges.push_back(e);
  }
  return edges;
}

std::vector<std::pair<double, int>> shortest_paths(
    std::vector<std::vector<double>> graph_matrix, int root) {
  int n = graph_matrix.size();
  assert(root >= 0 && root < n);

  std::vector<int> to_visit;
  for (int i = 0; i < n; i++) to_visit.push_back(i);

  // (distance, parent index) pairs
  std::vector<std::pair<double, int>> dp(n, {INFINITY, -1});
  dp[root].first = 0;

  while (n--) {
    // Take the closest not yet finalized vertex to the root
    auto it = std::min_element(
        to_visit.begin(), to_visit.end(),
        [dp](int v1, int v2) { return dp[v1].first < dp[v2].first; });
    int next = *it;
    // Remove it from `to_visit`
    *it = to_visit.back();
    to_visit.pop_back();
    // Update the distances and parents for the vertices in to_visit
    for (int v : to_visit) {
      double distance = dp[next].first + graph_matrix[next][v];
      if (distance < dp[v].first) dp[v] = {distance, next};
    }
  }

  return dp;
}

std::vector<std::pair<double, int>> shortest_paths(
    std::vector<std::vector<std::pair<double, int>>> graph, int root) {
  assert(root >= 0 && root < graph.size());
  std::priority_queue<std::pair<double, int>,
                      std::vector<std::pair<double, int>>,
                      std::greater<std::pair<double, int>>>
      pq;
  pq.push({0, root});

  // (distance, parent index) pairs
  std::vector<std::pair<double, int>> dp(graph.size(), {INFINITY, -1});
  dp[root].first = 0;

  while (!pq.empty()) {
    auto [distance, closest] = pq.top();
    assert(distance >= 0);
    pq.pop();
    if (distance > dp[closest].first) continue;
    for (const auto& [weight, neighbor] : graph[closest]) {
      if (dp[closest].first + weight < dp[neighbor].first) {
        dp[neighbor] = {dp[closest].first + weight, closest};
        pq.push({dp[neighbor].first, neighbor});
      }
    }
  }

  return dp;
}
