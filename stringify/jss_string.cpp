#include "jss_string.h"

namespace JSON
{
    std::ostream& stringify (std::ostream& stream, std::string const& name, std::string const& value, StringificationOptions const& options)
    {
        WRITE_NAME(stream);
        stream << '"';
        for (auto const& i : value)
        {
            if (i == '"' || i == '\\')
                stream.put('\\');
            stream.put(i);
        }
        stream << '"';
        return stream;
    }
}
