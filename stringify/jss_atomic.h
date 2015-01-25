#ifndef JSS_ATOMIC_H_INCLUDED
#define JSS_ATOMIC_H_INCLUDED

#include "jss_core.h"
#include <atomic>

namespace JSON
{
    template <typename T,
              typename = typename std::enable_if <Internal::can_js_stringify<T>::value>::type >
    std::string js_stringify(const std::string& name, std::atomic<T> const& value, StringificationOptions const& options)
    {
        return js_stringify(name, value.load(), options);
    }
}

#endif // JSS_ATOMIC_H_INCLUDED
