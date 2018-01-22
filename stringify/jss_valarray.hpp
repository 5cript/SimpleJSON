#pragma once

// has no allocator and therefore is not compatible in jss_container
#include "jss_optional.hpp"

#include <valarray>

namespace JSON
{
    template <typename T>
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::valarray <T> const& values, StringificationOptions const& options = {},
                            typename std::enable_if<Internal::can_stringify<T>::value>::type* = nullptr)
    {
        using namespace Internal;

        WRITE_ARRAY_START(stream);
        auto noNameOption = options;
        noNameOption.ignore_name = true;

        bool first = true;
        for (auto const& i : values)
        {
            if (Internal::is_optional_set(i))
            {
                if (!first)
                    stream << options.delimiter;
                stringify(stream, {}, i, noNameOption);
                first = false;
            }
        }
        WRITE_ARRAY_END(stream);
        return stream;
    }
}
