#ifndef JSS_MAP_H_INCLUDED
#define JSS_MAP_H_INCLUDED

#include "jss_core.h"
#include <map>

namespace JSON
{
    namespace Internal
    {
        template <typename T,
                  typename = typename std::enable_if <Internal::can_js_stringify<T>::value>::type >
        std::string js_stringify_map_pair(std::pair <const std::string, T> const& value, StringificationOptions const& options)
        {
            return js_stringify(value.first, value.second, options);
        }

        template <typename KeyT, typename ValueT,
                  typename = typename std::enable_if <Internal::can_js_stringify<ValueT>::value && Internal::can_js_stringify<KeyT>::value>::type >
        std::string js_stringify_map_pair_2(std::pair <const KeyT, ValueT> const& value, StringificationOptions const& options)
        {
            return js_stringify({}, value.first, options) + options.delimiter + js_stringify({}, value.second, options);
        }
    }

    template <typename ValueT, typename CompareT = std::less <ValueT>, class AllocT = std::allocator <ValueT>,
              typename = typename std::enable_if <Internal::can_js_stringify<ValueT>::value>::type >
    std::string js_stringify(std::string const& name, std::map<std::string, ValueT, CompareT, AllocT> const& values, StringificationOptions options)
    {
        using namespace Internal;
        options.in_object = true;

        std::stringstream sstr;
        WRITE_OBJECT_START(sstr);
        if (!values.empty())
        {
            APPLY_IO_MANIPULATERS(sstr);
            auto bfe = values.end();
            bfe--;
            for (auto i = values.begin(); i != bfe; ++i)
            {
                sstr << js_stringify_map_pair(*i, options);
                sstr << options.delimiter;
            }
            sstr << js_stringify_map_pair(*values.rbegin(), options);
        }
        WRITE_OBJECT_END(sstr);
        return sstr.str();
    }

    template <typename KeyT, typename ValueT, typename CompareT = std::less <ValueT>, class AllocT = std::allocator <ValueT>,
              typename = typename std::enable_if <Internal::can_js_stringify<ValueT>::value>::type >
    std::string js_stringify(std::string const& name, std::multimap<KeyT, ValueT, CompareT, AllocT> const& values, StringificationOptions options)
    {
        using namespace Internal;

        std::stringstream sstr;
        WRITE_ARRAY_START(sstr);
        if (!values.empty())
        {
            options.ignore_name = true;
            APPLY_IO_MANIPULATERS(sstr);
            auto bfe = values.end();
            bfe--;
            for (auto i = values.begin(); i != bfe; ++i)
            {
                WRITE_ARRAY_START(sstr);
                sstr << js_stringify_map_pair_2(*i, options);
                WRITE_ARRAY_END(sstr);
                sstr << options.delimiter;
            }
            WRITE_ARRAY_START(sstr);
            sstr << js_stringify_map_pair_2(*values.rbegin(), options);
            WRITE_ARRAY_END(sstr);
        }
        WRITE_ARRAY_END(sstr);
        return sstr.str();
    }
}

#endif // JSS_MAP_H_INCLUDED
