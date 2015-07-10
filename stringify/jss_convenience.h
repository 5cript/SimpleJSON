#ifndef JSS_CONVENIENCE_H_INCLUDED
#define JSS_CONVENIENCE_H_INCLUDED

#include "jss_core.h"
#include "jss_check.h"


namespace JSON
{
    template <typename T>
    std::ostream& try_stringify(std::ostream& stream, std::string const& name, T const& obj, StringificationOptions const& options = DEFAULT_OPTIONS,
                                   typename std::enable_if <Internal::can_stringify<T>::value, void>::type* = nullptr)
    {
        stringify(stream, name, obj, options);
        return stream;
    }

    template <typename T>
    std::ostream& try_stringify(std::ostream& stream, std::string const&, T const&, StringificationOptions const& = DEFAULT_OPTIONS,
                                 typename std::enable_if <!Internal::can_stringify<T>::value, int>::type* = nullptr)
    {
        static_assert (Internal::can_stringify<T>::value, "the object you try to convert is not convertible to JSON");
        return stream;
    }
}

#define json_serialize(NAME, STREAM) JSON::js_try_stringify(STREAM, #NAME, NAME)
#define json_serialize_opt(NAME, STREAM, OPTIONS) JSON::js_try_stringify(STREAM, #NAME, NAME, OPTIONS)

#endif // JSS_CONVENIENCE_H_INCLUDED
