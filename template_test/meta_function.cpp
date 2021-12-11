#include <type_traits>
#include <tuple>

template <template <class...> class MetaFunction>
struct lambda {
  template <typename... Args>
  struct apply {
    using type = typename MetaFunction<Args...>::type;
  };
};

template <typename, typename>
struct map;

template <typename Lambda, template <class...> class List, typename... Elements>
struct map<Lambda, List<Elements...>> {

  template <typename T>
  using call = typename Lambda::template apply<T>::type;
  using type = List<call<Elements>...>;

};

using no_pointers = map<lambda<std::remove_pointer>, std::tuple<int*, double**, float>>::type;

int main()
{
  no_pointers v = std::tuple<int, double*, float>{0, nullptr, 0.5};
}
