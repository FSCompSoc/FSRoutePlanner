#include "dijkstra.hpp"

using namespace std;

namespace fscompsoc::route_planner {
  size_t node::pick_minimum() {
    size_t lowest = 0;
    for(size_t i = 1; i < n; i++)
      if (weights[i] < weights[lowest])
        lowest = i;

    return lowest;
  }

  void node::_dijkstra_internal(
    vector<bool>& S,
    vector<optional<Weight>>& D,
    vector<optional<size_t>>& P,
    graph& g
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

  vector<Weight> graph::dijkstra() {
    vector<bool> S(n, false);

    vector<optional<Weight>> D(n, nullopt);
    D[0] = 0;

    vector<optional<size_t>> P(n, nullopt);
    P[0] = 0;

    nodes[0]._dijkstra_internal(S, D, P, *this);

    cout << "D:" << endl;
    for(size_t i = 0; i < n; i++)
      cout << "\t" << (D[i] ? to_string(*D[i]) : "null") << endl;

    cout << "P:" << endl;
    for(size_t i = 0; i < n; i++)
      cout << "\t" << (P[i] ? to_string(*P[i]) : "null") << endl;

    vector<Weight> ret(n);
    for(size_t i = 0; i < n; i++) ret[i] = *D[i];
    return ret;
  }

  graph::graph(weight_matrix matrix) : n(matrix.size()) {
    for(size_t i = 0; i < n; i++)
      nodes.emplace_back(node(i, n));

    for(size_t i = 0; i < n; i++)
      for(size_t j = 0; j < n; j++)
        nodes[i].weights[j] = matrix[i][j];
  }
}
