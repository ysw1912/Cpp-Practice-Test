#include <iostream>
#include <vector>
#include <unordered_map>

#include <boost/variant.hpp>

class Foo {
 public:
  explicit Foo() { std::cout << "default ctor\n"; }
  explicit Foo(int n) : n_(new int{n}) { std::cout << "arg ctor\n"; }
  ~Foo() {
    delete n_;
    std::cout << "dtor\n";
  }
  Foo(const Foo& f) {
    n_ = new int{*f.n_};
    std::cout << "copy ctor\n";
  }
  Foo(Foo&& f) noexcept {
    *this = std::move(f);
    std::cout << "move ctor\n";
  }
  Foo& operator=(const Foo& f) {
    n_ = new int{*f.n_};
    std::cout << "copy assign\n";
    return *this;
  }
  Foo& operator=(Foo&& f)
  {
    n_ = f.n_;
    f.n_ = nullptr;
    std::cout << "move assign\n";
    return *this;
  }

  int Val() { return *n_; }

 private:
  int* n_ = nullptr;
};


int main(int argc, char *argv[]) {
  boost::variant<Foo, std::vector<Foo>> a;
  std::unordered_map<std::string, boost::variant<Foo, std::vector<Foo>>> map;
  map["k1"] = Foo(666);
  map["k2"] = std::vector<Foo>{Foo(1)};
  boost::get<std::vector<Foo>>(map["k2"]).emplace_back(Foo(2));

  auto &i = boost::get<Foo>(map[std::string("k1")]);
  std::cout << i.Val() << "\n";
  auto &p = boost::get<std::vector<Foo>>(map[std::string("k2")]);
  for (auto &e : p) {
    std::cout << e.Val() << "\n";
  }
  return 0;
}