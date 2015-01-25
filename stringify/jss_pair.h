#ifndef JSS_PAIR_H_INCLUDED
#define JSS_PAIR_H_INCLUDED

#include "jss_object.h"
#include <utility>

namespace JSON
{
    template <typename KeyT, typename ValueT,
              typename = typename std::enable_if <Internal::can_js_stringify<KeyT>::value && Internal::can_js_stringify<ValueT>::value>::type >
    std::string js_stringify(std::string const& name, std::pair <KeyT, ValueT> const& value, StringificationOptions const& options)
    {
        std::stringstream sstr;
        WRITE_OBJECT_START(sstr);
        sstr << js_stringify("first", value.first, options);
        sstr << options.delimiter;
        sstr << js_stringify("second", value.second, options);
        WRITE_OBJECT_END(sstr);
        return sstr.str();
    }
}

#endif // JSS_PAIR_H_INCLUDED
