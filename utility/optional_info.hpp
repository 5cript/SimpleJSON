#pragma once

#include "../utility/tmp_util/fundamental/eval_if.hpp"
#include "../utility/tmp_util/fundamental/is_same.hpp"
#include "../utility/tmp_util/fundamental/null_type.hpp"

#include <boost/optional.hpp>

#ifdef __has_include                           // Check if __has_include is present
#   if __has_include(<optional>)                // Check for a standard library
#       include <optional>
#   elif __has_include(<experimental/optional>) // Check for an experimental version
#       include <experimental/optional>
#   endif
#endif

namespace JSON
{
    namespace Internal
    {
        template <typename T>
        struct has_value_type {
            typedef char yes[1];
            typedef char no[2];

            template <typename C>
            static yes& test(typename C::value_type*);

            template <typename>
            static no& test(...);

            constexpr static const bool value = sizeof(test<T>(nullptr)) == sizeof(yes);
            using type = JSON::bool_ <value>;
        };

        template <typename T>
        using has_value_type_t = typename has_value_type <T>::type;

        struct get_value_type
        {
            template <typename T>
            struct apply
            {
                using type = typename T::value_type;
            };
        };

        template <typename T>
        struct is_optional
        {
            using __value_type = JSON::eval_if_default_t <has_value_type_t <T>, JSON::null_t, get_value_type, T>;
            using type_boost = JSON::eval_if_default_t <
                JSON::bool_ <!std::is_same <__value_type, JSON::null_t>::value>,
                JSON::false_,
                JSON::is_same,
                T,
                boost::optional <__value_type>
            >;
            using type_stl = JSON::eval_if_default_t <
                JSON::bool_ <!std::is_same <__value_type, JSON::null_t>::value>,
                JSON::false_,
                JSON::is_same,
                T,
                std::optional <__value_type>
            >;
            constexpr static const bool value = type_boost::value || type_stl::value;
        };

        template <typename T, bool _is_optional>
        struct is_optional_set_impl
        {
            static inline bool isSet(T&&) noexcept { return true; }
        };

        template <typename T>
        struct is_optional_set_impl <T, true>
        {
            static inline bool isSet(T&& t) noexcept { return t.operator bool(); }
        };

        template <typename T>
        inline bool is_optional_set(T&& t) noexcept {
            using decayed = typename std::decay <T>::type;
            return is_optional_set_impl <T, is_optional <decayed>::value>::isSet(std::forward <T> (t));
        }
    }
}
