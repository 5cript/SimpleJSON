#include "jss_string.h"

namespace JSON
{
    std::string js_stringify(std::string const& name, std::string const& value, StringificationOptions const& options)
    {
        std::stringstream sstr;
        WRITE_NAME(sstr);
        sstr << '"'
             << value
             << '"'
        ;
        return sstr.str();
    }
}
