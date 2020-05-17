#include <iostream>

template <typename T, T Val>
struct Int {
  static const T value = Val;
  using value_type = T;
};

template <bool Cond, typename Then, typename Else>
struct If;

template <typename Then, typename Else>
struct If<true, Then, Else> {
  using type = Then;
};

template <typename Then, typename Else>
struct If<false, Then, Else> {
  using type = Else;
};

template <bool Cond, typename Body>
struct WhileLoop;

template <typename Body>
struct WhileLoop<true, Body> {
  using type = typename WhileLoop<Body::next::condition, typename Body::next>::type;
};

template <typename Body>
struct WhileLoop<false, Body> {
  using type = typename Body::result;
};

template <typename Body>
struct While {
  using type = typename WhileLoop<Body::condition, Body>::type;
};

// 约定 LoopBody 循环体类型拥有
// 1) 静态数据成员 condition: 循环条件
// 2) 类型 result: 退出循环时的状态
// 3) 类型 next: 下次循环执行一次时的状态
// 以“求和循环体”为例
template <int res, int cur, int end>
struct SumLoop {
  static const bool condition = cur <= end;
  using result = Int<int, res>;
  using next = SumLoop<res + cur, cur + 1, end>;
};

template <int start, int end>
struct Sum {
  using type = SumLoop<0, start, end>;
};


int main() {
  std::cout << If<Int<int, 10>::value == 10, Int<int, 1>, Int<int, -1>>::type::value << std::endl;

  std::cout << While<Sum<1, 1>::type>::type::value << std::endl;
  std::cout << While<Sum<1, 2>::type>::type::value << std::endl;
  std::cout << While<Sum<1, 4>::type>::type::value << std::endl;
  std::cout << While<Sum<1, 10>::type>::type::value << std::endl;
  return 0;
}
