#include "jss_nested_json.hpp"

namespace JSON
{
    std::ostream& stringify(std::ostream& stream, std::string const& name, json_string const& value, StringificationOptions const& options)
    {
        SJSON_WRITE_NAME(stream);
        stream << value.json;
        return stream;
    }
}
