#include <vector>

#include "utils.h"

template <
    template <typename, typename>
    class Container = std::vector,
    typename F, class R>
auto py_map(F&& f, R&& inputs)
{
  using result_type = std::decay_t<decltype(f(*inputs.begin()))>;
  Container<result_type, std::allocator<result_type>> result;
  result.reserve(inputs.size());
  for (auto&& item : inputs) {
    result.push_back(f(item));
  }
  return result;
}


int main() {
  std::vector<int> vec{1, 2, 3, 4, 5};
  auto result = py_map([](int x){ return x * x; }, vec);
  PrintVector(result, result.size());
}
