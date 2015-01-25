#ifndef JSS_FUNDAMENTAL_H_INCLUDED
#define JSS_FUNDAMENTAL_H_INCLUDED

#include "jss_core.h"

namespace JSON
{
    // enums are classified as compound types, but really... its better suited here

    // ARITHMETIC
    template <typename T,
              class = typename std::enable_if<   std::is_arithmetic<T>::value
                                              || std::is_enum<T>::value         >::type >
    std::string js_stringify(std::string const& name, T value, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        std::stringstream sstr;
        APPLY_IO_MANIPULATERS(sstr);
        WRITE_NAME(sstr);
        sstr << value;
        return sstr.str();
    }
}

#endif // JSS_FUNDAMENTAL_H_INCLUDED
