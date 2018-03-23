#include "jss_void.hpp"

namespace JSON
{
    std::ostream& stringify(std::ostream& stream, std::string const& name, StringificationOptions const& options)
    {
        SJSON_WRITE_NAME(stream);
        return stream;
    }
}
