#ifndef MAP_COMMONS_H_INCLUDED
#define MAP_COMMONS_H_INCLUDED

#include "jss_core.h"
#include <utility>

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
}

#endif // MAP_COMMONS_H_INCLUDED