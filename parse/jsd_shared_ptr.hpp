#pragma once

#include "jsd_smart_ptr.hpp"

#include "../utility/polymorphy.hpp"

#include <memory>

namespace JSON
{
    template <typename T>
    void parse(std::shared_ptr <T>& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options = {})
    {
        internal::parse_smart_ptr(value, name, object, options);
    }
}
