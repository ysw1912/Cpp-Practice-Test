#include "absl/strings/match.h"
#include "handler.h"

#include <iostream>
#include <list>
#include <string>
#include <thread>
#include <unordered_map>

#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <utility>

using namespace boost::asio;

class SyncClient {
 public:
  SyncClient(io_service& ios, std::string&& username):
  sock_(ios), started_(true), username_(username) {}

  void connect(const ip::tcp::endpoint& ep) {
    sock_.connect(ep);
  }

  void write(const std::string& msg) { sock_.write_some(buffer(msg)); }

  void write_request() {
    write("ping\n");
  }

  void process_msg() {
    std::string msg(buff_, already_read_);
    if (boost::algorithm::starts_with(msg, "login")) {
      on_login();
    } else if (boost::algorithm::starts_with(msg, "ping")) {
      on_ping(msg);
    } else if (boost::algorithm::starts_with(msg, "clients")) {
      on_clients(msg);
    } else {
      std::cerr << "Invalid msg " << msg << std::endl;
    }
  }

  void read_answer() {
    already_read_ = 0;
    read(sock_, buffer(buff_),
        [this](const boost::system::error_code &err, size_t bytes){
            if (err) return 0;
            bool found = std::find(buff_, buff_ + bytes, '\n') < buff_ + bytes;
            return found ? 0 : 1;
        });
    process_msg();
  }

  void loop() {
    write("login " + username_ + "\n");
    read_answer();
    while (started_) {
      write_request();
      read_answer();
      std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 7000));
    }
  }
  std::string username() const { return username_; }

 private:
  void on_login() { do_ask_clients(); }
  void on_ping(const std::string & msg) {
    std::istringstream in(msg);
    std::string answer;
    in >> answer >> answer;
    if (answer == "client_list_changed") {
      do_ask_clients();
    }
  }

  void on_clients(const std::string& msg) {
    std::string clients = msg.substr(8);
    std::cout << username_ << ", new client list:" << clients;
  }

  void do_ask_clients() {
    write("ask_clients\n");
    read_answer();
  }

 private:
  ip::tcp::socket sock_;
  enum { max_msg = 1024 };
  int already_read_{};
  char buff_[max_msg]{};
  bool started_;
  std::string username_;
};


int main() {
  io_service ios;
  ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8000);
  SyncClient client(ios, "SyncClient");
  try {
    client.connect(ep);
    client.loop();
  } catch (boost::system::system_error& err) {
    std::cout << "Client terminated: " << err.what() << std::endl;
  }
  return 0;
}
