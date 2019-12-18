#include "jsd_nested_json.hpp"

#include <boost/property_tree/json_parser.hpp>

namespace JSON
{
    void parse(json_string& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options)
    {
        try
        {
            auto& subtree = object.tree.get_child(name);

            std::stringstream tmp;
            boost::property_tree::write_json(tmp, subtree);
            value.json = tmp.str();
        }
        catch (boost::property_tree::ptree_bad_data& exc)
        {
            SJSON_DEFAULT_PROPERTY_ERROR_HANDLER("", "");
        }
        catch (boost::property_tree::ptree_bad_path& exc)
        {
            SJSON_DEFAULT_PATH_ERROR_HANDLER("", "");
        }
    }
}
