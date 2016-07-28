#include "jss_void.hpp"

namespace JSON
{
    std::ostream& stringify(std::ostream& stream, std::string const& name, StringificationOptions const& options)
    {
        WRITE_NAME(stream);
        return stream;
    }
}
