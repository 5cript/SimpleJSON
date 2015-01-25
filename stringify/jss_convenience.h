#ifndef JSS_CONVENIENCE_H_INCLUDED
#define JSS_CONVENIENCE_H_INCLUDED

#include "jss_core.h"
#include "jss_check.h"


namespace JSON
{
    template <typename T>
    std::string js_try_stringify(std::string const& name, T const& obj, StringificationOptions const& options = DEFAULT_OPTIONS,
                                 typename std::enable_if <Internal::can_js_stringify<T>::value, void>::type* = nullptr)
    {
        return js_stringify(name, obj, options);
    }

    template <typename T>
    std::string js_try_stringify(std::string const&, T const&, StringificationOptions const& = DEFAULT_OPTIONS,
                                 typename std::enable_if <!Internal::can_js_stringify<T>::value, int>::type* = nullptr)
    {
        static_assert (Internal::can_js_stringify<T>::value, "the object you try to convert is not convertible to JSON");
        return {};
    }
}

#define js_serialize(NAME) JSON::js_try_stringify(#NAME, NAME)
#define js_serialize_opt(NAME, OPTIONS) JSON::js_try_stringify(#NAME, NAME, OPTIONS)

#endif // JSS_CONVENIENCE_H_INCLUDED
