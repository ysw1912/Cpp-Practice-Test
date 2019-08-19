#include "strings.h"

#include <string>
#include <vector>

#include "utils.h"

namespace strings {
namespace {

inline void InternalSplitString(const std::string& str, char delimiter,
                                std::vector<std::string>& result) {
  const char* p = str.data();
  const char* p_end = p + str.size();
  while (p != p_end) {
    if (*p == delimiter) {
      ++p;
    } else {
      const char* start = p;
      while (++p != p_end && *p != delimiter);
      result.emplace_back(start, p - start);
    }
  }
}

}  // namespace

std::vector<std::string> Split(const std::string& str, char delimiter) {
  std::vector<std::string> result;
  InternalSplitString(str, delimiter, result);
  return result;
}

}  // namespace strings
