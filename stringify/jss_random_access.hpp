#pragma once

#include "jss_core.hpp"
#include "container_traits.hpp"
#include "jss_object.hpp"
#include "jss_container.hpp"

namespace JSON
{
    template <typename T, template <typename, class = std::allocator <T> > class ContainerT >
    std::ostream& stringify (std::ostream& stream, std::string const& name, ContainerT <T> const& values, StringificationOptions const& options = {},
                                typename std::enable_if<has_random_access_iterator<T, ContainerT>::value>::type* = nullptr,
                                typename std::enable_if<Internal::can_stringify<typename ContainerT<T>::value_type>::value>::type* = nullptr)
    {
        Internal::stringify_i(stream, name, values, options);
        return stream;
    }
}
