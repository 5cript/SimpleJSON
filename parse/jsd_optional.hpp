#pragma once

#include "jsd_core.hpp"

#ifdef __has_include                           // Check if __has_include is present
#   if __has_include(<optional>)                // Check for a standard library
#       include <optional>
#       include "jsd_optional_stl.hpp"
#   elif __has_include(<experimental/optional>) // Check for an experimental version
#       include <experimental/optional>
#       include "jsd_optional_stl.hpp"
#   endif
#endif

#include <boost/optional.hpp>

namespace JSON
{
    template <typename T>
    void parse(boost::optional <T>& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options = {})
    {
        try
        {
            if (object.tree.get_optional <std::string> (name))
            {
                T v;
                parse(v, name, object, options);
                value = v;
            }
        }
        catch (boost::property_tree::ptree_bad_data& exc)
        {
			SJSON_DEFAULT_PROPERTY_ERROR_HANDLER(T(), T());
        }
        // cannot throw ptree_bad_path
    }
}
