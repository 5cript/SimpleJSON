#pragma once

#include "jsd_core.hpp"
#include "jsd_smart_ptr.hpp"

#include "../utility/polymorphy.hpp"

#include <type_traits>
#include <memory>

namespace JSON
{
    template <typename T, typename Deleter>
    void parse(std::unique_ptr <T, Deleter>& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options = {})
    {
        internal::parse_smart_ptr(value, name, object, options);
    }
}
