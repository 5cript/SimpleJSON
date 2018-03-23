#include "merge_defaults.hpp"

namespace JSON
{
//#####################################################################################################################
    bool merge_defaults(
        std::string& value,
        std::string const& name,
        PropertyTree const& object,
        PropertyTree* difference,
        ParsingOptions const& options
    )
    {
        SJSON_MERGE_DEFAULTS_HAS(name)
        {
            value = opt.get();
            return false;
        }
        SJSON_MERGE_DEFAULTS_DOES_NOT_HAVE
    }
//#####################################################################################################################
}
