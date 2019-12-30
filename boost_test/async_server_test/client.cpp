#include "handler.h"

#include <iostream>
#include <list>
#include <string>
#include <thread>
#include <unordered_map>

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

using namespace boost::asio;

class Connector
{
 public:

  Connector(io_service& ios, const std::string& ip, short port) : ios_(ios), socket_(ios),
                                                                server_addr_(ip::tcp::endpoint(ip::address::from_string(ip), port)), is_connected_(false), chk_thread_(nullptr)
  {
    CreateEventHandler(ios);
  }

  ~Connector() = default;

  bool Start() {
    event_handler_->GetSocket().async_connect(
        server_addr_, [this](const boost::system::error_code& error) {
          if (error) {
            HandleConnectError(error);
            return;
          }
          std::cout << "Connect ok" << std::endl;
          is_connected_ = true;
          event_handler_->Read();  // 连接成功后发起一个异步读的操作
    });
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return is_connected_;
  }

  bool IsConnected() const {
    return is_connected_;
  }

  void Send(char* data, int len) {
    if (!is_connected_)
      return;
    event_handler_->Write(data, len);
  }

  void AsyncSend(char* data, int len) {
    if (!is_connected_)
      return;
    event_handler_->Write(data, len);
  }

 private:
  void CreateEventHandler(io_service& ios) {
    event_handler_ = std::make_shared<Handler>(ios);
    event_handler_->SetCallBackError(
        [this](int conn_id){ HandleError(conn_id); });
  }

  void CheckConnect() {
    if (chk_thread_) {
      return;
    }
    chk_thread_ = std::make_shared<std::thread>(
        [this] {
          while (true) {
            if (!IsConnected()) {
              Start();
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
          }});
  }

  void HandleConnectError(const boost::system::error_code& error)
  {
    is_connected_ = false;
    std::cout << error.message() << std::endl;
    event_handler_->CloseSocket();
    CheckConnect();
  }

  void HandleError(int conn_id) {
    is_connected_ = false;
    CheckConnect();
  }

 private:
  io_service& ios_;
  ip::tcp::socket socket_;
  ip::tcp::endpoint server_addr_;
  std::shared_ptr<Handler> event_handler_;
  bool is_connected_;
  std::shared_ptr<std::thread> chk_thread_;  // 检测重连的线程
};


int main() {
  io_service ios;
  boost::asio::io_service::work work(ios);
  std::thread thd([&ios] { ios.run(); });

  Connector conn(ios, "127.0.0.1", 9900);
  conn.Start();

  if (!conn.IsConnected()) {
    return -1;
  }

  const int len = 512;
  char line[len] = "";
  while (std::cin.getline(line, sizeof(line))) {
    conn.Send(line, sizeof(line));
  }

  return 0;
}
