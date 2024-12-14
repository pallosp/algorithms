#pragma once

#include <utility>
#include <vector>

// Finds the shortest paths from root in a weighted directed graph represented
// as a matrix. The weight between missing edges should be INFINITY. Returns the
// nodes of the spanning tree as a list of (distance, parent vertex) pairs.
// The algorithm's complexity is O(V²).
std::vector<std::pair<double, int>> shortest_paths_dense_graph(
    std::vector<std::vector<double>> graph_matrix, int root);
