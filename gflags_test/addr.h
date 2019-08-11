#ifndef CPP_ADDR_H_
#define CPP_ADDR_H_

#include <stdint.h>

#include <gflags/gflags.h>

namespace inet {

DECLARE_string(ip);
DECLARE_int32(port);

static bool ValidatePort(const char* flag_name, int32_t value);

}  // namespace inet

#endif //CPP_ADDR_H_
