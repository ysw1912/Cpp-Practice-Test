#ifndef CPP_UTILS_H
#define CPP_UTILS_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#define DISALLOW_COPY(TypeName) \
  TypeName(const TypeName&) = delete; \
  TypeName& operator=(const TypeName&) = delete

bool IsPrime(int n);

#endif //CPP_UTILS_H
