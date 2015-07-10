#ifndef JSS_STRING_H_INCLUDED
#define JSS_STRING_H_INCLUDED

#include "jss_core.h"
#include "jss_vector.h"

namespace JSON
{
    std::ostream& stringify (std::ostream& stream, std::string const& name, std::string const& value, StringificationOptions const& options = DEFAULT_OPTIONS);
}

#endif // JSS_STRING_H_INCLUDED
