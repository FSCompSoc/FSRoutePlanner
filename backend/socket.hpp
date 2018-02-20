#pragma once

#include <functional>
#include <future>
#include <vector>
#include <cstdint>
#include <exception>
#include <memory>
#include <type_traits>

namespace fscompsoc::net {
  class socket {
  public:
    virtual std::future<std::vector<uint8_t>> receive();
    virtual std::future<bool> send(std::vector<uint8_t> data);
  };

  template<typename SocketType>
  class socket_server {
    static_assert(std::is_base_of_v<socket, SocketType>);

  public:
    virtual std::unique_ptr<SocketType> accept();
  };

  using any_socket_server = socket_server<socket>;

  class ip_address {
  public:
    int version;
    std::vector<uint8_t> bytes;
  };

  class ip_endpoint {
  public:
    ip_address addr;
    uint16_t port;
  };

  class tcp_socket : public socket {
  public:
    std::future<std::vector<uint8_t>> receive() override;
    std::future<bool> send(std::vector<uint8_t> data) override;

  public:
    tcp_socket(ip_endpoint server);

    ~tcp_socket();
  };

  class tcp_server : public socket_server<tcp_socket> {
  public:
    std::unique_ptr<tcp_socket> accept();
  };
}
