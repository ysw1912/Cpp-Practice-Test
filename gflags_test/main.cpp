#include <iostream>

#include "addr.h"

int main(int argc, char** argv) {
  inet::FLAGS_ip = "255.255.255.255";
  google::SetCommandLineOption("port", "123");

  google::ParseCommandLineFlags(&argc, &argv, true);

  printf("ip: %s\n", inet::FLAGS_ip.c_str());
  printf("port: %d\n", inet::FLAGS_port);

  google::ShutDownCommandLineFlags();
  return 0;
}
