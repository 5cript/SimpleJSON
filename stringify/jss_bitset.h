#ifndef JSS_BITSET_H_INCLUDED
#define JSS_BITSET_H_INCLUDED

#include "jss_core.h"
#include <bitset>
#include <iostream>

namespace JSON
{
    template <size_t Size, size_t TemplateRecursionMax = TemplateRecursionMaximum>
    std::string js_stringify(std::string const& name, std::bitset<Size> const& values, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        std::stringstream sstr;
        WRITE_ARRAY_START(sstr);
        for (unsigned i = 0; i < Size - 1; ++i)
        {
            sstr << values[i];
            sstr << options.delimiter;
        }
        sstr << values[Size - 1];
        WRITE_ARRAY_END(sstr);
        return sstr.str();
    }

    template <size_t Size>
    std::string js_stringify(std::string const& name, std::bitset<Size> const& values, StringificationOptions const& options = DEFAULT_OPTIONS,
                             typename std::enable_if <Size==0>::type* = nullptr)
    {
        std::stringstream sstr;
        WRITE_ARRAY_START(sstr);
        WRITE_ARRAY_END(sstr);
        return sstr.str();
    }
}

#endif // JSS_BITSET_H_INCLUDED
