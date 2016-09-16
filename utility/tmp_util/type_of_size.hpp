#pragma once

#include <cstdint>

namespace JSON
{
    template <unsigned>
    struct type_of_size
    {};

    template <>
    struct type_of_size <8>
    {
        using type = std::int8_t;
    };

    template <>
    struct type_of_size <16>
    {
        using type = std::int16_t;
    };

    template <>
    struct type_of_size <32>
    {
        using type = std::int32_t;
    };

    template <>
    struct type_of_size <64>
    {
        using type = std::int64_t;
    };
}
