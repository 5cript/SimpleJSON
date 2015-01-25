#ifndef JSD_CONVENIENC_H_INCLUDED
#define JSD_CONVENIENC_H_INCLUDED

#include "jsd_core.h"
#include "jsd_check.h"
#include "jsd_options.h"

namespace JSON
{
	template <typename T>
    void js_try_parse(T& obj, std::string const& name, PropertyTree const& tree, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS,
                                 typename std::enable_if <Internal::can_js_parse<T>::value, void>::type* = nullptr)
    {
        js_parse(obj, name, tree, options);
    }

    template <typename T>
    void js_try_parse(T&, std::string const&, PropertyTree const&, ParsingOptions const& = DEFAULT_PARSER_OPTIONS,
                                 typename std::enable_if <!Internal::can_js_parse<T>::value, int>::type* = nullptr)
    {
        static_assert (Internal::can_js_parse<T>::value, "the object you try to parse has no applicable interface");
    }
}

#define js_deserialize(NAME) JSON::js_try_parse(#NAME, NAME)
#define js_deserialize_opt(NAME, OPTIONS) JSON::js_try_parse(#NAME, NAME, OPTIONS)

#endif // JSD_CONVENIENCE_H_INCLUDED
