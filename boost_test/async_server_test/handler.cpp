#include "handler.h"

#include <iostream>


void Handler::Read() {
  //三种情况下会返回：
  //  1. 缓冲区满.
  //  2. transfer_at_least为真(收到特定数量字节即返回).
  //  3. 有错误发生.
  async_read(sock_, buffer(buff_), transfer_at_least(HEAD_LEN),
             [this](const boost::system::error_code& ec, size_t size) {
               if (ec) {
                 HandleError(ec);
                 return;
               }
               std::cout << buff_.data() + HEAD_LEN << std::endl;
               Read();
             });
}

void Handler::Write(char* data, int len) {
  boost::system::error_code ec;
  write(sock_, buffer(data, len), ec);
  if (ec) {
    HandleError(ec);
  }
}

ip::tcp::socket& Handler::GetSocket() {
  return sock_;
}

void Handler::CloseSocket() {
  boost::system::error_code ec;
  sock_.shutdown(ip::tcp::socket::shutdown_send, ec);
  sock_.close(ec);
}

void Handler::SetConnId(int conn_id) {
  conn_id_ = conn_id;
}

int Handler::GetConnId() const {
  return conn_id_;
}

void Handler::HandleError(const boost::system::error_code& ec) {
  CloseSocket();
  std::cout << ec.message() << std::endl;
  if (callback_)
    callback_(conn_id_);
}
