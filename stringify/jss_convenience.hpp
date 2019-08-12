#pragma once

#include "jss_core.hpp"
#include "jss_check.hpp"

#include "../utility/beauty_stream.hpp"

#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>

namespace JSON
{

    template <typename T>
    std::ostream& try_stringify_start(std::ostream& stream, std::string const& name, T const& obj, StringificationOptions const& options = {},
                                      typename std::enable_if <Internal::can_stringify<T>::value, void>::type* = nullptr)
    {
        stream.put('{');
        stringify(stream, name, obj, options);
        stream.put('}');
        return stream;
    }

    template <typename T>
    std::ostream& try_stringify(std::ostream& stream, std::string const& name, T const& obj, StringificationOptions const& options = {},
                                   typename std::enable_if <Internal::can_stringify<T>::value, void>::type* = nullptr)
    {
        stringify(stream, name, obj, options);
        return stream;
    }

    template <typename T>
    std::ostream& try_stringify(std::ostream& stream, std::string const&, T const&, StringificationOptions const& = {},
                                 typename std::enable_if <!Internal::can_stringify<T>::value, int>::type* = nullptr)
    {
        static_assert (Internal::can_stringify<T>::value, "the object you try to convert is not convertible to JSON");
        return stream;
    }

    /**
     *  Only works with files.
     */
    template <typename T>
    void try_stringify_beautiful(std::string const& file, std::string const& name, T const& obj, StringificationOptions const& opts = {})
    {
        boost::iostreams::filtering_ostream filter;

        filter.push(JSON::BeautifiedStreamWrapper{});
        filter.push(boost::iostreams::file_sink(file));

        JSON::try_stringify_start(filter, name, obj, opts);
    }
}

#define json_serialize(NAME, STREAM) JSON::try_stringify(STREAM, #NAME, NAME)
#define json_serialize_opt(NAME, STREAM, OPTIONS) JSON::try_stringify(STREAM, #NAME, NAME, OPTIONS)
