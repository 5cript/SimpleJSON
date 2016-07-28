#pragma once

#include "../utility/tmp_util/fundamental/eval_if.hpp"
#include "../utility/tmp_util/fundamental/is_same.hpp"
#include "../utility/tmp_util/fundamental/null_type.hpp"

// really want to swap with std::optional
#include <boost/optional.hpp>

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
            using type = mplex::bool_ <value>;
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
            using __value_type = mplex::eval_if_default_t <has_value_type_t <T>, mplex::null_t, get_value_type, T>;
            using type = mplex::eval_if_default_t <
                mplex::bool_ <!std::is_same <__value_type, mplex::null_t>::value>,
                mplex::false_,
                mplex::is_same,
                T,
                boost::optional <__value_type>
            >;
            constexpr static const bool value = type::value;
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

    template <typename T>
    std::ostream& stringify (std::ostream& stream, std::string const& name, boost::optional <T> const& value, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        // only write if actually existing
        if (value)
            return stringify (stream, name, value.value(), options);
        else
            return stream; // do nothing
    }
}
