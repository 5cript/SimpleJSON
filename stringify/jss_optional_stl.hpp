#pragma once

#ifdef __has_include                           // Check if __has_include is present
#if __has_include(<optional>)                // Check for a standard library
#include <optional>

namespace JSON
{
    template <typename T>
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::optional <T> const& value, StringificationOptions const& options = {})
    {
        // only write if actually existing
        if (value)
            return stringify(stream, name, value.value(), options);
        else
            return stream; // do nothing
    }
}

#endif
#endif
