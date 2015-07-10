#ifndef JSS_ARRAY_H_INCLUDED
#define JSS_ARRAY_H_INCLUDED

#include "jss_core.h"
#include "jss_struct.h"
#include "jss_iterator.h"
#include <array>

namespace JSON
{
    template <typename T, std::size_t N,
              typename = typename std::enable_if <Internal::can_stringify<T>::value>::type >
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::array<T, N> const& values, StringificationOptions options = DEFAULT_OPTIONS)
    {
        options.ignore_name = true;
        WRITE_ARRAY_START(stream);
        if (!values.empty())
        {
            for (auto i = values.begin(); i != values.end() - 1; ++i)
            {
                stringify(stream, {}, *i, options);
                stream << options.delimiter;
            }
            stream << values.back();
        }
        WRITE_ARRAY_END(stream);
        return stream;
    }
}

#endif // JSS_ARRAY_H_INCLUDED
