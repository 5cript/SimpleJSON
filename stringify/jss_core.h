#ifndef JSS_CORE_H_INCLUDED
#define JSS_CORE_H_INCLUDED

#include "jss_options.h"
#include "jss_error.h"

#include <type_traits>
#include <string>
#include <sstream>
#include <iterator>
#include <iomanip>
#include <iosfwd>

// stringify signature: (std::ostream& stream, std::string const&, T, StringificationOptions, SFINAE_ADDITIONS)

namespace JSON
{
/*
    std::string operator"" _s( const char* c_str, long unsigned length)
    {
        return std::string (c_str);
    }
*/

    constexpr auto TemplateRecursionMaximum = 8;

    #define CLASS_STRINGIFY_FUNCTION_NAME stringify
    #define APPLY_IO_MANIPULATERS(STREAM) options.io_options.apply(STREAM)

    #define WRITE_NAME(STREAM)                          \
    if (!options.ignore_name && options.in_object)      \
    {   STREAM << '"' << name << "\":";  }

    #define WRITE_OBJECT_START(STREAM)                  \
            WRITE_NAME(STREAM)                          \
    STREAM << "{"

    #define WRITE_ARRAY_START(STREAM)                   \
            WRITE_NAME(STREAM)                          \
    STREAM << "["

    #define WRITE_OBJECT_END(STREAM)                    \
    STREAM << "}"

    #define WRITE_ARRAY_END(STREAM)                     \
    STREAM << "]"
}

#endif // JSS_CORE_H_INCLUDED
