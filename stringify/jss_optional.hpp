#pragma once

#include "jss_core.hpp"

#include <boost/optional.hpp>

namespace JSON
{
    template <typename T>
    std::ostream& stringify (std::ostream& stream, std::string const& name, boost::optional <T> const& value, StringificationOptions const& options = {})
    {
        // only write if actually existing
        if (value)
            return stringify (stream, name, value.value(), options);
        else
            return stream; // do nothing
    }
}
