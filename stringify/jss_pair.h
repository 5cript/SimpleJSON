#ifndef JSS_PAIR_H_INCLUDED
#define JSS_PAIR_H_INCLUDED

#include "jss_object.h"
#include <utility>

namespace JSON
{
    template <typename KeyT, typename ValueT,
              typename = typename std::enable_if <Internal::can_stringify<KeyT>::value && Internal::can_stringify<ValueT>::value>::type >
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::pair <KeyT, ValueT> const& value, StringificationOptions options)
    {
        WRITE_OBJECT_START(stream);
        options.ignore_name = false;
        options.in_object = true;
        stringify(stream, "first", value.first, options);
        stream << options.delimiter;
        stringify(stream, "second", value.second, options);
        WRITE_OBJECT_END(stream);
        return stream;
    }
}

#endif // JSS_PAIR_H_INCLUDED
