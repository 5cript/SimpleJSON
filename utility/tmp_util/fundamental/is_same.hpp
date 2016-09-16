#pragma once

#include <type_traits>
#include "integral.hpp"

namespace JSON {
    struct is_same {
        template <typename T, typename U>
        struct apply {
            using type = bool_ <std::is_same<T, U>::value>;
            constexpr static const bool value = type::value;
        };
    };

    template <typename T>
    struct is_type {
        template <typename U>
        struct apply {
            using type = bool_ <std::is_same<T, U>::value>;
            constexpr static const bool value = type::value;
        };
    };
}
