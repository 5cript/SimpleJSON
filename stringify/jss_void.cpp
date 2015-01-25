#include "jss_void.h"

namespace JSON
{
    std::string js_stringify(std::string const& name, StringificationOptions const& options)
    {
        std::stringstream sstr;
        APPLY_IO_MANIPULATERS(sstr);
        WRITE_NAME(sstr);
        return sstr.str();
    }
}
