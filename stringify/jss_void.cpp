#include "jss_void.h"

namespace JSON
{
    std::ostream& stringify(std::ostream& stream, std::string const& name, StringificationOptions const& options)
    {
        WRITE_NAME(stream);
        return stream;
    }
}
