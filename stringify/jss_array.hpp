#pragma once

#include "jss_core.hpp"
#include "jss_iterator.hpp"
#include "jss_optional.hpp"
#include <array>

namespace JSON
{
    template <typename T, std::size_t N,
              typename = typename std::enable_if <Internal::can_stringify<T>::value>::type >
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::array<T, N> const& values, StringificationOptions options = {})
    {
        WRITE_ARRAY_START(stream);
        options.ignore_name = true;
        bool first = true;
        for (auto const& i : values)
        {
            if (Internal::is_optional_set(i))
            {
                if (!first)
                    stream << options.delimiter;
                stringify(stream, {}, i, options);
                first = false;
            }
        }
        WRITE_ARRAY_END(stream);
        return stream;
    }
}
