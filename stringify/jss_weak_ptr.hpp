#pragma once

#include "jss_core.hpp"
#include "jss_smart_ptr.hpp"
#include "../utility/polymorphy.hpp"

#include <memory>


namespace JSON
{
    template <typename T,
              typename = typename std::enable_if <
                Internal::can_stringify<T>::value ||
                !std::is_same <typename polydecls <T>::type, no_poly>::value
              >::type >
    std::ostream& stringify (std::ostream& stream, const std::string& name, std::weak_ptr<T> const& value, StringificationOptions const& options = {})
    {
        if (value.expired())
            throw WeakPtrExpiredException{};

        return internal::stringify_smart_ptr(stream, name, value, options);
    }

}
