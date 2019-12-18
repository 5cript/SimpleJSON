#pragma once

#include "jss_core.hpp"

#include "../utility/string_is_json.hpp"

namespace JSON
{
    std::ostream& stringify(std::ostream& stream, std::string const& name, json_string const& value, StringificationOptions const& options = {});
}
