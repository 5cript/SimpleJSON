#pragma once

#include "jsd_core.hpp"

#include "../utility/string_is_json.hpp"

namespace JSON
{
    void parse(json_string& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options = {});
}
