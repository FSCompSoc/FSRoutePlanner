#pragma once

#include "dijkstra.hpp"
#include "socket.hpp"

#include <functional>
#include <future>
#include <vector>
#include <cstdint>

namespace fscompsoc::route_planner {
  class table_server {
  private:
    net::any_socket_server _server;

  public:
    std::future<graph> get_graph();

  public:
    table_server();

    ~table_server();
  };
}
