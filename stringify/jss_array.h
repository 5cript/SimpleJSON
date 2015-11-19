#ifndef JSS_ARRAY_H_INCLUDED
#define JSS_ARRAY_H_INCLUDED

#include "jss_core.h"
#include "jss_iterator.h"
#include "jss_optional.h"
#include <array>

namespace JSON
{
    template <typename T, std::size_t N,
              typename = typename std::enable_if <Internal::can_stringify<T>::value>::type >
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::array<T, N> const& values, StringificationOptions options = DEFAULT_OPTIONS)
    {
        options.ignore_name = true;
        WRITE_ARRAY_START(stream);
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

#endif // JSS_ARRAY_H_INCLUDED
