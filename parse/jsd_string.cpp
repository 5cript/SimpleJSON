#include "jsd_string.hpp"

namespace JSON {

void parse(std::string& value, std::string const& name,
           PropertyTree const& object, ParsingOptions const& options)
{
    try
    {
        GET_VALUE(std::string, name, value, "");
    }
    catch (boost::property_tree::ptree_bad_data& exc)
    {
        DEFAULT_PROPERTY_ERROR_HANDLER("", "");
    }
    catch (boost::property_tree::ptree_bad_path& exc)
    {
        DEFAULT_PATH_ERROR_HANDLER("", "");
    }
}

} // JSON
