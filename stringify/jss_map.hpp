#pragma once

#include "jss_core.hpp"
#include "jss_optional.hpp"
#include "map_commons.hpp"
#include <map>

namespace JSON
{
    template <typename ValueT, typename CompareT = std::less <ValueT>, class AllocT = std::allocator <ValueT>,
              typename = typename std::enable_if <Internal::can_stringify<ValueT>::value>::type >
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::map<std::string, ValueT, CompareT, AllocT> const& values, StringificationOptions options)
    {
        using namespace Internal;

        WRITE_OBJECT_START(stream);
        options.in_object = true;

        bool first = true;
        for (auto const& i : values)
        {
            if (is_optional_set(i.second))
            {
                if (!first)
                    stream << options.delimiter;
                stringify_map_pair(stream, i, options);
                first = false;
            }
        }
        WRITE_OBJECT_END(stream);
        return stream;
    }

    template <typename KeyT, typename ValueT, typename CompareT = std::less <ValueT>, class AllocT = std::allocator <ValueT>,
              typename = typename std::enable_if <Internal::can_stringify<ValueT>::value>::type >
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::multimap<KeyT, ValueT, CompareT, AllocT> const& values, StringificationOptions options)
    {
        using namespace Internal;

        WRITE_ARRAY_START(stream);
        options.ignore_name = true;

        bool first = true;
        for (auto const& i : values)
        {
            if (is_optional_set(i.second))
            {
                if (!first)
                    stream << options.delimiter;
                WRITE_ARRAY_START(stream);
                stringify_map_pair_2(stream, i, options);
                WRITE_ARRAY_END(stream);
                first = false;
            }
        }
        WRITE_ARRAY_END(stream);
        return stream;
    }
}
