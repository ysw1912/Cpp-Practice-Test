// std::declval 与 std::result_of
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Person
{
  std::string name;
  int age;
};

std::ostream& operator<<(std::ostream &out, const Person &p) {
  out << "(" << p.name << ", " << p.age << ")";
  return out;
}

template<typename Fn>
std::multimap<decltype(std::declval<Fn>()(std::declval<Person>())), Person>
    GroupBy(const std::vector<Person>& vec, const Fn& key_selector)
{
  typedef decltype(key_selector(*(Person*)nullptr)) key_type;
  std::multimap<key_type, Person> map;
  for (auto& p: vec) {
      map.insert(std::make_pair(key_selector(p), p));
  }
  return map;
}

int main() {
  std::vector<Person> vec = {{"ana", 40}, {"cindy", 56}, {"baby", 1}, {"bob", 25}, {"ana", 12}, {"cindy", 25}};
  auto map = GroupBy(vec, [](const Person& person){ return person.age; });
  for (auto& p : map) {
    std::cout << p.second << ' ';
  }
  std::cout << std::endl;

  auto map2 = GroupBy(vec, [](const Person& person){ return person.name; });
  for (auto& p : map2) {
    std::cout << p.second << ' ';
  }
  std::cout << std::endl;
  return 0;
}
