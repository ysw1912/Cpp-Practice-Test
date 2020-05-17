#include <iostream>

#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;


int main() {
  io_service service;
  string s;
  cin >> s;
  windows::stream_handle sd_in(service, GetStdHandle(STDIN_FILENO));
  char data[512];
  sd_in.async_read_some(buffer(data, 512), [&data](boost::system::error_code, size_t){
      cout << "Read " << data << "===" << endl;
  });
  service.run();

  system("pause");
  return 0;
}
