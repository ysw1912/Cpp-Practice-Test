#ifndef CPP_HANDLER_H_
#define CPP_HANDLER_H_

#include <functional>

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

using namespace boost::asio;
using boost::system::error_code;

const int MAX_IP_PACK_SIZE = 65536;
const int HEAD_LEN = 4;

class Handler
{
 public:

  explicit Handler(io_service& ios) : sock_(ios) { }

  ~Handler() = default;

  void Read();

  void Write(char* data, int len);

  ip::tcp::socket& GetSocket();

  void CloseSocket();

  void SetConnId(int conn_id);

  int GetConnId() const;

  template<typename F>
  void SetCallBackError(F f) {
    callback_ = f;
  }

 private:
  void HandleError(const boost::system::error_code& ec);

 private:
  ip::tcp::socket sock_;
  std::array<char, MAX_IP_PACK_SIZE> buff_ = {};
  int conn_id_ = -1;
  std::function<void(int)> callback_;
};

#endif //CPP_HANDLER_H_
