#ifndef JSS_UNIQUE_PTR_H_INCLUDED
#define JSS_UNIQUE_PTR_H_INCLUDED

#include "jss_core.h"
#include <memory>

namespace JSON
{
    template <typename T,
              typename = typename std::enable_if <Internal::can_stringify<T>::value>::type >
    std::ostream& stringify(std::ostream& stream, const std::string& name, std::unique_ptr<T> const& value, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        if (!value)
            throw UniquePtrNullptrException{};
        return stringify(stream, name, *value, options);
    }
}

#endif // JSS_UNIQUE_PTR_H_INCLUDED
