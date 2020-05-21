#include "output.h"

#include <vector>
#include <map>


int main() {
  std::cout << "[is pair]" << std::endl;
  std::cout << "int: " << is_pair_v<int> << std::endl;
  std::cout << "std::pair<int, int>: " << is_pair_v<std::pair<int, int>>
            << std::endl;
  std::cout << "[has key type]" << std::endl;
  std::cout << "int: " << has_key_type<int>::value << std::endl;
  std::cout << "std::map<int, std::string>: "
            << has_key_type<std::map<int, std::string>>::value << std::endl;
  std::cout << "[can output]" << std::endl;
  std::cout << "float: " << can_output_v<float> << std::endl;
  std::cout << "std::string: " << can_output_v<std::string> << std::endl;
  std::cout << "std::pair<int, int>: " << can_output_v<std::pair<int, int>>
            << std::endl;
  std::cout << "std::vector<int>: " << can_output_v<std::vector<int>>
            << std::endl;

  std::cout << "=================================================" << std::endl;
  std::pair<std::string, int> p1{"a", 1}, p2{"b", 2}, p3{"c", 3};
  std::vector<std::pair<std::string, int>> vec{p1, p2, p3};
  std::cout << vec << std::endl;

  return 0;
}
