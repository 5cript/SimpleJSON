#ifndef JSS_MAP_H_INCLUDED
#define JSS_MAP_H_INCLUDED

#include "jss_core.h"
#include "jss_optional.h"
#include <map>

namespace JSON
{
    namespace Internal
    {
        template <typename T,
                  typename = typename std::enable_if <Internal::can_stringify<T>::value>::type >
        void stringify_map_pair (std::ostream& stream, std::pair <const std::string, T> const& value, StringificationOptions const& options)
        {
            stringify(stream, value.first, value.second, options);
        }

        template <typename KeyT, typename ValueT,
                  typename = typename std::enable_if <Internal::can_stringify<ValueT>::value && Internal::can_stringify<KeyT>::value>::type >
        void stringify_map_pair_2 (std::ostream& stream, std::pair <const KeyT, ValueT> const& value, StringificationOptions const& options)
        {
            stringify(stream, {}, value.first, options);
            stream << options.delimiter;
            stringify(stream, {}, value.second, options);
        }
    }

    template <typename ValueT, typename CompareT = std::less <ValueT>, class AllocT = std::allocator <ValueT>,
              typename = typename std::enable_if <Internal::can_stringify<ValueT>::value>::type >
    std::ostream& stringify (std::ostream& stream, std::string const& name, std::map<std::string, ValueT, CompareT, AllocT> const& values, StringificationOptions options)
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

#endif // JSS_MAP_H_INCLUDED
