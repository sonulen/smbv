#pragma once

#include <optional>
#include <type_traits>

namespace mtl {

template <typename T>
class optional;

template <typename>
struct is_optional : std::false_type {};

template <typename T>
struct is_optional<std::optional<T>> : std::true_type {};

template <typename T>
struct is_optional<const std::optional<T>> : std::true_type {};

template <typename T>
struct is_optional<std::optional<T>&> : std::true_type {};

template <typename T>
struct is_optional<const std::optional<T>&> : std::true_type {};

}  // namespace mtl
