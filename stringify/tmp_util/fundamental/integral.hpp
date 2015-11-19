#ifndef MPLEX_FUNDAMENTAL_INTEGRAL_HPP_INCLUDED
#define MPLEX_FUNDAMENTAL_INTEGRAL_HPP_INCLUDED

#include <type_traits>
#include <cstdint>

namespace mplex
{
    template <typename T, T Value>
    using integral = std::integral_constant <T, Value>;

#define DECLARE_INTEGRAL(TYPE) \
    template <TYPE V> \
    using TYPE ## _ = mplex::integral <TYPE, V>

#define DECLARE_INTEGRAL_N(TYPE, NAME) \
    template <TYPE V> \
    using NAME ## _ = mplex::integral <TYPE, V>

    DECLARE_INTEGRAL(bool);
    DECLARE_INTEGRAL(int);
    DECLARE_INTEGRAL(long);
    DECLARE_INTEGRAL_N(long long, long_long);
    DECLARE_INTEGRAL(short);
    DECLARE_INTEGRAL(unsigned);

    DECLARE_INTEGRAL_N(unsigned int, unsigned_int);
    DECLARE_INTEGRAL_N(unsigned long, unsigned_long);
    DECLARE_INTEGRAL_N(unsigned long long, unsigned_long_long);
    DECLARE_INTEGRAL_N(unsigned short, unsigned_short);

    DECLARE_INTEGRAL(uint8_t);
    DECLARE_INTEGRAL(uint16_t);
    DECLARE_INTEGRAL(uint32_t);
    DECLARE_INTEGRAL(uint64_t);

    DECLARE_INTEGRAL(int8_t);
    DECLARE_INTEGRAL(int16_t);
    DECLARE_INTEGRAL(int32_t);
    DECLARE_INTEGRAL(int64_t);

    using true_ = bool_ <true>;
    using false_ = bool_ <false>;
}

#endif // MPLEX_FUNDAMENTAL_INTEGRAL_HPP_INCLUDED
