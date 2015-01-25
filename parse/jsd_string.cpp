#include "jsd_string.h"

namespace JSON {

void js_parse(std::string& value, std::string const& name,
              PropertyTree const& object, ParsingOptions const& options)
{
    try
    {
        value = object.tree.get<std::string>(name);
    }
    catch (boost::property_tree::ptree_bad_data& exc)
    {
        DEFAULT_ERROR_HANDLER("", "<undefined>");
    }
}

} // JSON
