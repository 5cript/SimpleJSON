#include "jsd_string.hpp"
#include "../utility/base64.hpp"

namespace JSON {

void parse(std::string& value, std::string const& name,
           PropertyTree const& object, ParsingOptions const& options)
{
    try
    {
        if (!options.strings_are_binary)
        {
            GET_VALUE(std::string, name, value, "");
        }
        else
        {
            std::string encoded;
            GET_VALUE(std::string, name, encoded, "");
            decodeBase64 <char, std::basic_string> (encoded, value);
        }
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
