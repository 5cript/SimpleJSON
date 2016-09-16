#pragma once

#include <type_traits>
#include <cstdint>

namespace JSON
{
    template <typename T, T Value>
    using integral = std::integral_constant <T, Value>;

#define JSON_DECLARE_INTEGRAL(TYPE) \
    template <TYPE V> \
    using TYPE ## _ = JSON::integral <TYPE, V>

#define JSON_DECLARE_INTEGRAL_N(TYPE, NAME) \
    template <TYPE V> \
    using NAME ## _ = JSON::integral <TYPE, V>

    JSON_DECLARE_INTEGRAL(bool);
    JSON_DECLARE_INTEGRAL(int);
    JSON_DECLARE_INTEGRAL(long);
    JSON_DECLARE_INTEGRAL_N(long long, long_long);
    JSON_DECLARE_INTEGRAL(short);
    JSON_DECLARE_INTEGRAL(unsigned);

    JSON_DECLARE_INTEGRAL_N(unsigned int, unsigned_int);
    JSON_DECLARE_INTEGRAL_N(unsigned long, unsigned_long);
    JSON_DECLARE_INTEGRAL_N(unsigned long long, unsigned_long_long);
    JSON_DECLARE_INTEGRAL_N(unsigned short, unsigned_short);

    JSON_DECLARE_INTEGRAL(uint8_t);
    JSON_DECLARE_INTEGRAL(uint16_t);
    JSON_DECLARE_INTEGRAL(uint32_t);
    JSON_DECLARE_INTEGRAL(uint64_t);

    JSON_DECLARE_INTEGRAL(int8_t);
    JSON_DECLARE_INTEGRAL(int16_t);
    JSON_DECLARE_INTEGRAL(int32_t);
    JSON_DECLARE_INTEGRAL(int64_t);

    using true_ = bool_ <true>;
    using false_ = bool_ <false>;
}
