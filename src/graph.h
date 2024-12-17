#pragma once

#include <utility>
#include <vector>

// Converts a weighted directed graph from adjacency matrix to adjacency list
// representation.
std::vector<std::vector<std::pair<double, int>>> graph_matrix_to_edges(
    std::vector<std::vector<double>> graph);

// Finds the shortest paths from root in a weighted directed graph specified
// as an adjacency matrix. The weights must be ≥0. Missing edges can be
// indicated with INFINITY weights.
//
// Returns the nodes of the spanning tree as a list of (distance, parent node)
// pairs. The parent node of the root node is -1.
//
// The algorithm's complexity is O(V²).
std::vector<std::pair<double, int>> shortest_paths(
    std::vector<std::vector<double>> graph_matrix, int root);

// Finds the shortest paths from root in a weighted directed graph specified as
// adjacency list with Dijkstra's algorithm. The edge weights must be ≥0.
//
// Returns the nodes of the spanning tree as a list of (distance, parent node)
// pairs. The parent node of the root node is -1.
//
// The algorithm's complexity is O(E log(V)).
std::vector<std::pair<double, int>> shortest_paths(
    std::vector<std::vector<std::pair<double, int>>> graph_edges, int root);
