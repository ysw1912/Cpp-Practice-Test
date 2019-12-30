// 函数链式调用
#include <iostream>
#include <type_traits>

template<typename OuterFn, typename InnerFn>
class Composed
{
 public:
  explicit Composed(OuterFn outer, InnerFn inner):
  outer_(outer), inner_(inner) {}

 public:
  //
  // -> decltype(std::declval<OuterFn>()((std::declval<InnerFn>()(std::declval<T>()))))
  // -> decltype(std::declval<OuterFn>()(std::result_of_t<InnerFn(T)>()))
  template<typename T>
  auto operator()(T arg) -> std::result_of_t<OuterFn(std::result_of_t<InnerFn(T)>)>
  {
    return outer_(inner_(arg));
  }

 private:
  InnerFn inner_;
  OuterFn outer_;
};

template <typename Func1, typename Func2>
Composed<Func1, Func2> Compose(Func1 f1, Func2 f2) {
  return Composed<Func1, Func2>(f1, f2);
}

template <typename Func1, typename Func2, typename Func3, typename... Funcs>
auto Compose(Func1 f1, Func2 f2, Func3 f3, Funcs... fs)
  -> decltype(Compose(Compose(f1, f2), f3, fs...))
{
  return Compose(Compose(f1, f2), f3, fs...);
}

int main() {
  auto f1 = [](int x){ return x + 1; };
  auto f2 = [](int x){ return x + 2; };
  auto f3 = [](int x){ return x + 3; };
  auto f4 = [](int x){ return x + 4; };
  auto f5 = [](int x){ return x + 5; };

  auto ret = Compose(f1, f2, f3)(0);
  std::cout << ret << std::endl;
  ret = Compose(f1, f2, f3, f4)(0);
  std::cout << ret << std::endl;
  ret = Compose(f1, f2, f3, f4, f5)(0);
  std::cout << ret << std::endl;
  ret = Compose([](int x){ return x * 2; }, [](int x){ return x * 3; })(3);
  std::cout << ret << std::endl;
  return 0;
}
