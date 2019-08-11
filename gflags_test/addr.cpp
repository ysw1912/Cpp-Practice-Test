#include "addr.h"

namespace inet {

DEFINE_string(ip, "127.0.0.1", "connect ip");
DEFINE_int32(port, 80, "listen port");

bool ValidatePort(const char* flag_name, int32_t value) {
  if (value > 0 && value < 32768)
    return true;
  printf("Invalid value for --%s: %d\n", flag_name, value);
  return false;
}

DEFINE_validator(port, &ValidatePort);

}  // namespace inet
