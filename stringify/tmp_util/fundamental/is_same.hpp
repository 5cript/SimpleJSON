#ifndef IS_SAME_HPP_INCLUDED
#define IS_SAME_HPP_INCLUDED

#include <type_traits>
#include "integral.hpp"

namespace mplex {
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

#endif // IS_SAME_HPP_INCLUDED
