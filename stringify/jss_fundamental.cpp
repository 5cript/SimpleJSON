#include "jss_fundamental.hpp"

namespace JSON
{
    std::ostream& stringify(std::ostream& stream, std::string const& name, char value, StringificationOptions const& options)
    {
        SJSON_WRITE_NAME(stream);
        stream << "\"" << value << "\"";
        return stream;
    }

    std::ostream& stringify(std::ostream& stream, std::string const& name, wchar_t value, StringificationOptions const& options)
    {
        SJSON_WRITE_NAME(stream);
        stream << "\"" << value << "\"";
        return stream;
    }
}
