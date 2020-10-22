#pragma once

#include <type_traits>

namespace ksys {

template <class T, class...>
struct IsAnyOfType : std::false_type {};
template <class T, class Head, class... Tail>
struct IsAnyOfType<T, Head, Tail...>
    : std::conditional_t<std::is_same_v<T, Head>, std::true_type, IsAnyOfType<T, Tail...>> {};

}  // namespace ksys
