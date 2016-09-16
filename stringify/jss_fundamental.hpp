#pragma once

#include "jss_core.hpp"

namespace JSON
{
    // enums are classified as compound types, but really... its better suited here

    // ARITHMETIC
    template <typename T,
              class = typename std::enable_if<  (std::is_arithmetic<T>::value && !std::is_same<T, char>::value && !std::is_same<T, wchar_t>::value)
                                              && !std::is_enum<T>::value         >::type >
    std::ostream& stringify(std::ostream& stream, std::string const& name, T value, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        WRITE_NAME(stream);
        stream << value;
        return stream;
    }

    std::ostream& stringify(std::ostream& stream, std::string const& name, char value, StringificationOptions const& options = DEFAULT_OPTIONS);
    std::ostream& stringify(std::ostream& stream, std::string const& name, wchar_t value, StringificationOptions const& options = DEFAULT_OPTIONS);
}
