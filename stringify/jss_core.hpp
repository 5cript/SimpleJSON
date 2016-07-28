#ifndef JSS_CORE_H_INCLUDED
#define JSS_CORE_H_INCLUDED

#include "jss_options.hpp"
#include "jss_error.hpp"

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

    inline std::ostream& stringify_object_start(std::ostream& stream, std::string const& name, StringificationOptions const& options)
    {
        WRITE_OBJECT_START(stream);
        return stream;
    }
    inline std::ostream& stringify_object_end(std::ostream& stream)
    {
        WRITE_OBJECT_END(stream);
        return stream;
    }

    class object_scope
    {
    public:
        object_scope(std::ostream& stream, std::string const& name, StringificationOptions& options)
            : stream_(stream)
            , options_(options)
        {
            options_.in_object = true;
            stringify_object_start(stream_, name, options);
        }

        ~object_scope()
        {
            stringify_object_end(stream_);
            options_.in_object = false;
        }

        object_scope& operator=(object_scope const&) = delete;
        object_scope& operator=(object_scope&&) = delete;
        object_scope(object_scope const&) = delete;
        object_scope(object_scope&&) = delete;

    private:
        std::ostream& stream_;
        StringificationOptions& options_;
    };

    #define JSON_OBJECT_STRINGIFY(stream, options) object_scope(stream, options) _json_os__;
}

#endif // JSS_CORE_H_INCLUDED
