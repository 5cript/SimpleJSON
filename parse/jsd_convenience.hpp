#pragma once

#include "jsd_core.hpp"
#include "jsd_check.hpp"
#include "jsd_options.hpp"

namespace JSON
{
	template <typename T>
    void try_parse(T& obj, std::string const& name, PropertyTree const& tree, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS,
                   typename std::enable_if <Internal::can_parse<T>::value, void>::type* = nullptr)
    {
        parse(obj, name, tree, options);
    }

    template <typename T>
    void try_parse(T&, std::string const&, PropertyTree const&, ParsingOptions const& = DEFAULT_PARSER_OPTIONS,
                   typename std::enable_if <!Internal::can_parse<T>::value, int>::type* = nullptr)
    {
        static_assert (Internal::can_parse<T>::value, "the object you try to parse has no applicable interface");
    }

    template <typename T>
    T make_from_json(std::istream&& stream)
    {
        T res;
        JSON::parse(res, "", JSON::parse_json(stream));
        return res;
    }

    template <typename T>
    T make_from_json(std::istream& stream)
    {
        T res;
        JSON::parse(res, "", JSON::parse_json(stream));
        return res;
    }

    template <typename T>
    T make_from_json(std::string const& str)
    {
        T res;
        JSON::parse(res, "", JSON::parse_json(str));
        return res;
    }
}

#define json_deserialize(NAME) JSON::try_parse(#NAME, NAME)
#define json_deserialize_opt(NAME, OPTIONS) JSON::try_parse(#NAME, NAME, OPTIONS)
