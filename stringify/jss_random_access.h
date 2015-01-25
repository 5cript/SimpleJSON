#ifndef JSS_RANDOM_ACCESS_H_INCLUDED
#define JSS_RANDOM_ACCESS_H_INCLUDED

#include "jss_core.h"
#include "container_traits.h"
#include "jss_object.h"
#include "jss_container.h"

namespace JSON
{
    template <typename T, template <typename, class = std::allocator <T> > class ContainerT >
    std::string js_stringify(std::string const& name, ContainerT <T> const& values, StringificationOptions const& options = DEFAULT_OPTIONS,
                             typename std::enable_if<has_random_access_iterator<T, ContainerT>::value>::type* = nullptr,
                             typename std::enable_if<Internal::can_js_stringify<typename ContainerT<T>::value_type>::value>::type* = nullptr)
    {
        return Internal::js_stringify_i(name, values, [](ContainerT <T> const& c) { return c.end() - 1; }, options);
    }
}

#endif // JSS_RANDOM_ACCESS_H_INCLUDED
