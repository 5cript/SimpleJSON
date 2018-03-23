#pragma once

#include "jss_core.hpp"
#include "jss_optional.hpp"
#include "map_commons.hpp"
#include <unordered_map>

namespace JSON
{
    template <typename ValueT, typename HashT = std::hash <std::string>, class PredT = std::equal_to <std::string>,
              typename AllocT = std::allocator <std::pair <const std::string, ValueT>>,
              typename = typename std::enable_if <Internal::can_stringify<ValueT>::value>::type >
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::unordered_map<std::string, ValueT, HashT, PredT, AllocT> const& values, StringificationOptions options)
    {
        using namespace Internal;

        SJSON_WRITE_OBJECT_START(stream);
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
        SJSON_WRITE_OBJECT_END(stream);
        return stream;
    }

    template <typename KeyT,
              typename ValueT, typename HashT = std::hash <std::string>, class PredT = std::equal_to <std::string>,
              typename AllocT = std::allocator <std::pair <const std::string, ValueT>>,
              typename = typename std::enable_if <Internal::can_stringify<ValueT>::value>::type >
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::unordered_multimap<KeyT, ValueT, HashT, PredT, AllocT> const& values, StringificationOptions options)
    {
        using namespace Internal;

        SJSON_WRITE_ARRAY_START(stream);
        options.ignore_name = true;

        bool first = true;
        for (auto const& i : values)
        {
            if (is_optional_set(i.second))
            {
                if (!first)
                    stream << options.delimiter;
                SJSON_WRITE_ARRAY_START(stream);
                stringify_map_pair_2(stream, i, options);
                SJSON_WRITE_ARRAY_END(stream);
                first = false;
            }
        }
        SJSON_WRITE_ARRAY_END(stream);
        return stream;
    }
}
