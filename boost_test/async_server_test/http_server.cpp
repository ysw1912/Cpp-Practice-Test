#include <iostream>
#include <string>
#include <memory>

#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

class HttpConnection: public std::enable_shared_from_this<HttpConnection>
{
 public:
  explicit HttpConnection(boost::asio::io_context& io): socket_(io) {}

  void Start() {
    auto conn_ptr = shared_from_this();
    boost::asio::async_read_until(
        socket_, boost::asio::dynamic_buffer(request_), "\r\n\r\n",
        [conn_ptr, this](const boost::system::error_code& err, size_t len) {
          if(err) {
            cout<<"recv err:"<<err.message()<<"\n";
            return;
          }
          cout << "Request: " << request_ << "\n";
          string first_line = request_.substr(0, request_.find("\r\n")); // should be like: GET / HTTP/1.0
          cout << "Header: " << first_line << "\n";
          // process with request
          // ...

          char str[] = "HTTP/1.0 200 OK\r\n\r\n"
                       "<html>hello from http server</html>";
          boost::asio::async_write(
              socket_, boost::asio::buffer(str),
              [this](const boost::system::error_code& err, size_t len) {
                cout << "Close connection\n";
                socket_.close();
              });
        });
  }

  boost::asio::ip::tcp::socket& Socket() { return socket_; }
 private:
  boost::asio::ip::tcp::socket socket_;
  string request_;
};

class HttpServer
{
 public:
  HttpServer(boost::asio::io_context& io,
      const boost::asio::ip::tcp::endpoint& ep): io_(io), acceptor_(io, ep) {}

  void Start() {
    auto conn_ptr = std::make_shared<HttpConnection>(io_);
    acceptor_.async_accept(
        conn_ptr->Socket(),
        [conn_ptr, this](const boost::system::error_code& err) {
          if(err) {
            cout << "accept err:" << err.message() << "\n";
            return;
          }
          conn_ptr->Start();
          Start();
        });
  }
 private:
  boost::asio::io_context& io_;
  boost::asio::ip::tcp::acceptor acceptor_;
};

int main(int argc, const char* argv[]) {
  if(argc != 3) {
    cout << "usage: httpsvr ip port\n";
    return 0;
  }

  boost::asio::io_context io;
  boost::asio::ip::tcp::endpoint ep(
      boost::asio::ip::make_address(argv[1]), std::stoi(argv[2]));
  HttpServer server(io, ep);
  server.Start();
  io.run();
  return 0;
}
