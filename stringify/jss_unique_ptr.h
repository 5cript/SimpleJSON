#ifndef JSS_UNIQUE_PTR_H_INCLUDED
#define JSS_UNIQUE_PTR_H_INCLUDED

#include "jss_core.h"
#include "jss_smart_ptr.h"
#include "../utility/polymorphy.h"

#include <memory>

namespace JSON
{
    template <typename T, typename Deleter,
              typename = typename std::enable_if <
                Internal::can_stringify<T>::value ||
                !std::is_same <typename polydecls <T>::type, no_poly>::value
              >::type >
    std::ostream& stringify(std::ostream& stream, const std::string& name, std::unique_ptr<T, Deleter> const& value, StringificationOptions const& options = {})
    {
        if (!value)
            throw UniquePtrNullptrException{};

        internal::stringify_smart_ptr(stream, name, value, options);
    }
}

#endif // JSS_UNIQUE_PTR_H_INCLUDED
