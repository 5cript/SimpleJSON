#pragma once

#include "jss_core.hpp"

#include <boost/optional.hpp>

#ifdef __has_include                           // Check if __has_include is present
#   if __has_include(<optional>)                // Check for a standard library
#       include <optional>
#       include "jss_optional_stl.hpp"
#   elif __has_include(<experimental/optional>) // Check for an experimental version
#       include <experimental/optional>
#       include "jss_optional_stl.hpp"
#   endif
#endif

namespace JSON
{
    template <typename T>
    std::ostream& stringify(std::ostream& stream, std::string const& name, boost::optional <T> const& value, StringificationOptions const& options = {})
    {
        // only write if actually existing
        if (value)
            return stringify(stream, name, value.value(), options);
        else
            return stream; // do nothing
    }
}
