#ifndef CPP_STRINGS_H_
#define CPP_STRINGS_H_

#include <string>
#include <vector>

namespace strings {

std::vector<std::string> Split(const std::string &str, char delimiter);

inline bool StartsWith(const std::string& str, const std::string& prefix) {
  if (str == prefix) return true;
  const size_t str_size = str.size();
  const size_t prefix_size = prefix.size();
  return str_size >= prefix_size and str.compare(0, prefix_size, prefix) == 0;
}

inline bool EndsWith(const std::string& str, const std::string& suffix) {
  if (str == suffix) return true;
  const size_t str_size = str.size();
  const size_t suffix_size = suffix.size();
  return str_size >= suffix_size and
         str.compare(str_size - suffix_size, suffix_size, suffix) == 0;
}

}  // namespace strings

#endif //CPP_STRINGS_H_
