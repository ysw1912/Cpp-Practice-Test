#include "handler.h"

#include <iostream>
#include <list>
#include <unordered_map>

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

using namespace boost::asio;

const int MaxConnectionNum = 65536;
const int MaxRecvSize = 65536;

class Server
{
 public:

  Server(io_service& ios, short port) : ios_(ios),
      acceptor_(ios, ip::tcp::endpoint(ip::tcp::v4(), port)),
      conn_id_list(MaxConnectionNum) {
    int current = 0;
    std::generate_n(conn_id_list.begin(), MaxConnectionNum,
                    [&current] { return ++current; });
  }

  ~Server() = default;

  void Accept()
  {
    std::cout << "Start Listening " << std::endl;
    std::shared_ptr<Handler> handler = CreateHandler();

    acceptor_.async_accept(handler->GetSocket(),
        [this, handler](const boost::system::error_code& error) {
          if (error) {
            std::cout << error.value() << " " << error.message() << std::endl;
            HandleAcceptError(handler, error);
        }

        handler_map_.insert(std::make_pair(handler->GetConnId(), handler));
        std::cout << "current connect count: " << handler_map_.size()
        << std::endl;
        handler->Read();
        Accept();
    });
  }

 private:
  void HandleAcceptError(const std::shared_ptr<Handler>& event_handler,
      const boost::system::error_code& error) {
    std::cout << "Error，error reason：" << error.value() << error.message()
    << std::endl;
    //关闭socket，移除读事件处理器
    event_handler->CloseSocket();
    StopAccept();
  }

  void StopAccept() {
    boost::system::error_code ec;
    acceptor_.cancel(ec);
    acceptor_.close(ec);
    ios_.stop();
  }

  std::shared_ptr<Handler> CreateHandler() {
    int connId = conn_id_list.front();
    conn_id_list.pop_front();
    std::shared_ptr<Handler> handler = std::make_shared<Handler>(ios_);
    handler->SetConnId(connId);
    handler->SetCallBackError([this](int connId) { RecycleConnId(connId); });
    return handler;
  }

  void RecycleConnId(int connId)
  {
    auto it = handler_map_.find(connId);
    if (it != handler_map_.end()) {
      handler_map_.erase(it);
    }
    std::cout << "current connect count: " << handler_map_.size() << std::endl;
    conn_id_list.push_back(connId);
  }

 private:
  io_service& ios_;
  ip::tcp::acceptor acceptor_;
  std::unordered_map<int, std::shared_ptr<Handler>> handler_map_;
  std::list<int> conn_id_list;
};

int main() {
  io_service ios;
  //boost::asio::io_service::work work(ios);
  //std::thread thd([&ios]{ios.run(); });

  Server server(ios, 9900);
  server.Accept();
  ios.run();

  //thd.join();
}
