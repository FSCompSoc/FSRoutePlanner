#include "dijkstra.hpp"
#include <fscompsoc/net/socket.hpp>

using namespace fscompsoc::net;

int main(int argc, char const *argv[]) {
  ip_address addr("127.0.0.1");
  ip_endpoint ep(addr, 10000);
  tcp_socket sock(ep);
  return 0;
}
