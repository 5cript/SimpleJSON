#pragma once

#include "jss_core.hpp"
#include "jss_check.hpp"


namespace JSON
{

    template <typename T>
    std::ostream& try_stringify_start(std::ostream& stream, std::string const& name, T const& obj, StringificationOptions const& options = DEFAULT_OPTIONS,
                                      typename std::enable_if <Internal::can_stringify<T>::value, void>::type* = nullptr)
    {
        stream.put('{');
        stringify(stream, name, obj, options);
        stream.put('}');
        return stream;
    }

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

#define json_serialize(NAME, STREAM) JSON::try_stringify(STREAM, #NAME, NAME)
#define json_serialize_opt(NAME, STREAM, OPTIONS) JSON::try_stringify(STREAM, #NAME, NAME, OPTIONS)
