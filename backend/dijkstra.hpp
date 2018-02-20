#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <optional>
#include <cstdint>
#include <array>
#include <map>
#include <cstring>

using namespace std;

template <typename Weight, size_t n>
class graph;

template <typename Weight, size_t n>
class node {
  static_assert(n > 1);

  friend graph<Weight, n>;

public:
  size_t id;
  array<optional<Weight>, n> weights;

private:
  size_t pick_minimum() {
    size_t lowest = 0;
    for(size_t i = 1; i < n; i++)
      if (weights[i] < weights[lowest])
        lowest = i;

    return lowest;
  }

  void _dijkstra_internal(
    array<bool, n>& S,
    array<optional<Weight>, n>& D,
    array<optional<size_t>, n>& P,
    graph<Weight, n>& g
  ) {
    cout << "Entered " << id << endl;
    S[id] = true;

    for(size_t i = 0; i < n; i++) {
      if(!weights[i]) continue;
      // Calculate distance from root to nodes
      Weight distance = *D[id] + *weights[i];
      if (!D[i] || distance < *D[i]) {
        D[i] = distance;
        P[i] = id;
        g.nodes[i]._dijkstra_internal(S, D, P, g);
      }
    }

  }

public:
  node(size_t id) : id(id) {}
  node() = default;
};

template <typename Weight, size_t n>
using weight_matrix = optional<Weight>[n][n];

template <typename Weight, size_t n>
class graph {
  static_assert(n > 1);

public:
  array<node<Weight, n>, n> nodes;

public:
  array<Weight, n> dijkstra() {
    array<bool, n> S;
    S.fill(false);

    array<optional<Weight>, n> D;
    D.fill(nullopt);
    D[0] = 0;

    array<optional<size_t>, n> P;
    P.fill(nullopt);
    P[0] = 0;

    nodes[0]._dijkstra_internal(S, D, P, *this);

    cout << "D:" << endl;
    for(size_t i = 0; i < n; i++)
      cout << "\t" << (D[i] ? to_string(*D[i]) : "null") << endl;

    cout << "P:" << endl;
    for(size_t i = 0; i < n; i++)
      cout << "\t" << (P[i] ? to_string(*P[i]) : "null") << endl;

    array<Weight, n> ret;
    for(size_t i = 0; i < n; i++) ret[i] = *D[i];
    return ret;
  }

public:
  graph(weight_matrix<Weight, n> matrix) {
    for(size_t i = 0; i < n; i++)
      nodes[i] = node<Weight, n>(i);

    for(size_t i = 0; i < n; i++)
      for(size_t j = 0; j < n; j++)
        nodes[i].weights[j] = matrix[i][j];
  }
};
