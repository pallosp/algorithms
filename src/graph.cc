#include "graph.h"

#include <algorithm>
#include <utility>
#include <vector>

std::vector<std::pair<double, int>> shortest_paths_dense_graph(
    std::vector<std::vector<double>> g, int root) {
  int n = g.size();
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
      double distance = dp[next].first + g[next][v];
      if (distance < dp[v].first) dp[v] = {distance, next};
    }
  }

  return dp;
}
