#ifndef JSS_ARRAY_H_INCLUDED
#define JSS_ARRAY_H_INCLUDED

#include "jss_core.h"
#include "jss_struct.h"
#include "jss_iterator.h"
#include <array>

namespace JSON
{
    template <typename T, std::size_t N,
              typename = typename std::enable_if <Internal::can_js_stringify<T>::value>::type >
    std::string js_stringify(std::string const& name, std::array<T, N> const& values, StringificationOptions options = DEFAULT_OPTIONS)
    {
        std::stringstream sstr;
        options.ignore_name = true;
        WRITE_ARRAY_START(sstr);
        if (!values.empty())
        {
            for (auto i = values.begin(); i != values.end() - 1; ++i)
            {
                sstr << js_stringify({}, *i, options);
                sstr << options.delimiter;
            }
            sstr << values.back();
        }
        WRITE_ARRAY_END(sstr);
        return sstr.str();
    }
}

#endif // JSS_ARRAY_H_INCLUDED
