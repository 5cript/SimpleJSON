#include "jss_string.h"

namespace JSON
{
    std::ostream& stringify (std::ostream& stream, std::string const& name, std::string const& value, StringificationOptions const& options)
    {
        WRITE_NAME(stream);
        stream << '"'
               << value
               << '"'
        ;
        return stream;
    }
}
