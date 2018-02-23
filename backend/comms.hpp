#pragma once

#include "dijkstra.hpp"
#include <fscompsoc/net/socket.hpp>

#include <functional>
#include <memory>
#include <vector>
#include <cstdint>

namespace fscompsoc::route_planner {
  class table_server {
  private:
    std::unique_ptr<net::any_socket_server> _server;

  public:
    std::future<graph> get_graph();

  public:
    table_server();

    ~table_server();
  };
}
