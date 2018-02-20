#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <optional>
#include <cstdint>
#include <array>
#include <map>
#include <cstring>

namespace fscompsoc::route_planner {

  using Weight = double;

  class GraphTooSmall : std::exception {};

  class graph;

  class node {
    friend graph;

  public:
    size_t id;
    const size_t n;
    std::vector<std::optional<Weight>> weights;

  private:
    size_t pick_minimum();

    void _dijkstra_internal(
      std::vector<bool>& S,
      std::vector<std::optional<Weight>>& D,
      std::vector<std::optional<size_t>>& P,
      graph& g
    );

  public:
    node(size_t id, size_t n) : id(id), n(n) {
      if(n < 2) throw(GraphTooSmall());
    }

    node(node&&) = default;
  };

  using weight_matrix = std::vector<std::vector<std::optional<Weight>>>;

  class graph {
  public:
    std::vector<node> nodes;
    const size_t n;

  public:
    std::vector<Weight> dijkstra();

  public:
    graph(weight_matrix matrix);
  };

}
