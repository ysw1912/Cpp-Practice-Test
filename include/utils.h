#ifndef CPP_UTILS_H
#define CPP_UTILS_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#define DISALLOW_COPY(TypeName) \
  TypeName(const TypeName&) = delete; \
  TypeName& operator=(const TypeName&) = delete

template <typename T>
void PrintVector(const std::vector<T>& vec, size_t size) {
  std::copy(vec.begin(), vec.begin() + size, std::ostream_iterator<T>(std::cout, " "));
  std::cout << std::endl;
}

bool IsPrime(int n);

#endif //CPP_UTILS_H
