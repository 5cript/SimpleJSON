#pragma once

#include "jsd_core.hpp"

#include "../utility/rename.hpp"

namespace JSON
{
    template <typename T, typename Name>
    void parse(rename <T, Name>& value, std::string const& name, PropertyTree const& object, ParsingOptions const& options = {})
    {
        // this is kinda dirty.
        std::string relName;
        auto pos = name.find_last_of(".");
        if (pos == std::string::npos)
            relName = Name::c_str;
        else
            relName = name.substr(0, pos + 1) + Name::c_str;

        // now parse
        parse(value.getValue(), relName, object, options);
    }
}
