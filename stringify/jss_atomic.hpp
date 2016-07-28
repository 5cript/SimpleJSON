#ifndef JSS_ATOMIC_H_INCLUDED
#define JSS_ATOMIC_H_INCLUDED

#include "jss_core.hpp"
#include <atomic>

namespace JSON
{
    template <typename T,
              typename = typename std::enable_if <Internal::can_stringify<T>::value>::type >
    std::ostream& stringify (std::ostream& stream, const std::string& name, std::atomic<T> const& value, StringificationOptions const& options)
    {
        stringify(stream, name, value.load(), options);
        return stream;
    }
}

#endif // JSS_ATOMIC_H_INCLUDED
