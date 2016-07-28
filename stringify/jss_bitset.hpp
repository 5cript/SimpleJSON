#pragma once

#include "jss_core.hpp"
#include <bitset>
#include <iostream>

namespace JSON
{
    template <size_t Size, size_t TemplateRecursionMax = TemplateRecursionMaximum>
    std::ostream& stringify (std::ostream& stream, std::string const& name, std::bitset<Size> const& values, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        WRITE_ARRAY_START(stream);
        for (unsigned i = 0; i < Size - 1; ++i)
        {
            stream << values[i];
            stream << options.delimiter;
        }
        stream << values[Size - 1];
        WRITE_ARRAY_END(stream);
        return stream;
    }

    template <size_t Size>
    std::ostream& stringify (std::ostream& stream, std::string const& name, std::bitset<Size> const& values, StringificationOptions const& options = DEFAULT_OPTIONS,
                                typename std::enable_if <Size==0>::type* = nullptr)
    {
        WRITE_ARRAY_START(stream);
        WRITE_ARRAY_END(stream);
        return stream;
    }
}
