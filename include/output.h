#ifndef CPP_OUTPUT_H
#define CPP_OUTPUT_H

#include <iostream>
#include <type_traits>
#include <utility>

template <typename T>
struct is_pair : std::false_type {};

template <typename T1, typename T2>
struct is_pair<std::pair<T1, T2>> : std::true_type {};

template <typename T>
constexpr bool is_pair_v = is_pair<T>::value;

template <typename T, typename = std::void_t<>>
struct has_key_type : std::false_type {};

template <typename T>
struct has_key_type<T, std::void_t<typename T::key_type>> : std::true_type {};

template <typename T, typename = std::void_t<>>
struct can_output : std::false_type {};

template <typename T>
struct can_output<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<T>())>> : std::true_type {};

template <typename T>
constexpr bool can_output_v = can_output<T>::value;

template <typename Container, typename = std::enable_if_t<!can_output_v<Container>>>
auto operator<<(std::ostream& os, const Container& container)
    -> decltype(container.begin(), container.end(), os) {
  using element_type = std::decay_t<decltype(*container.begin())>;
  std::pair<char, char> brackets = GetBrackets(has_key_type<Container>());
  os << brackets.first;
  for (auto it = container.begin(); it != container.end(); ++it) {
    if (it != container.begin()) {
      os << ", ";
    }
    OutputElement(os, *it, container, is_pair<element_type>());
  }
  os << brackets.second;
  return os;
}

std::pair<char, char> GetBrackets(std::true_type) {
  return std::make_pair('{', '}');
}

std::pair<char, char> GetBrackets(std::false_type) {
  return std::make_pair('[', ']');
}

template <typename Elem, typename Container>
auto OutputElement(std::ostream& os, const Elem& element, const Container&, std::true_type)
-> decltype(std::declval<typename Container::key_type>(), os) {
  os << element.first << ": " << element.second;
  return os;
}

template <typename Elem, typename Container>
std::ostream& OutputElement(std::ostream& os, const Elem& element, const Container&, ...) {
  os << element;
  return os;
}

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& pair) {
  os << '(' << pair.first << ", " << pair.second << ')';
  return os;
}

#endif // CPP_OUTPUT_H
