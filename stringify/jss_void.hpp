#pragma once

#include "jss_core.hpp"

namespace JSON
{
    std::ostream& stringify(std::ostream& stream, std::string const& name, StringificationOptions const& options = DEFAULT_OPTIONS);
}
