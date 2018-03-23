#include "jss_string.hpp"
#include "../utility/base64.hpp"

namespace JSON
{
    std::ostream& stringify (std::ostream& stream, std::string const& name, std::string const& value, StringificationOptions const& options)
    {
        SJSON_WRITE_NAME(stream);
        stream << '"';
        if (!options.strings_are_binary)
        {
            if (options.escape_strings)
            {
                for (auto const& i : value)
                {
                    if (i == '"' || i == '\\')
                        stream.put('\\');
                    stream.put(i);
                }
            }
            else
                stream << value;
        }
        else
        {
            encodeBase64 <char, std::basic_string> (stream, value);
        }
        stream << '"';
        return stream;
    }
}
