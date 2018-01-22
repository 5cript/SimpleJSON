#pragma once

#include "jss_core.hpp"
#include "jss_vector.hpp"

namespace JSON
{
    std::ostream& stringify (std::ostream& stream, std::string const& name, std::string const& value, StringificationOptions const& options = {});
}
