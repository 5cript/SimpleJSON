#include "jss_fundamental.h"

namespace JSON
{
    std::ostream& stringify(std::ostream& stream, std::string const& name, char value, StringificationOptions const& options)
    {
        APPLY_IO_MANIPULATERS(stream);
        WRITE_NAME(stream);
        stream << "\"" << value << "\"";
        return stream;
    }

    std::ostream& stringify(std::ostream& stream, std::string const& name, wchar_t value, StringificationOptions const& options)
    {
        APPLY_IO_MANIPULATERS(stream);
        WRITE_NAME(stream);
        stream << "\"" << value << "\"";
        return stream;
    }
}
