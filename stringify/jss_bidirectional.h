#ifndef JSS_BIDIRECTIONAL_H_INCLUDED
#define JSS_BIDIRECTIONAL_H_INCLUDED

#include "jss_core.h"
#include "container_traits.h"
#include "jss_object.h"
#include "jss_container.h"

namespace JSON
{
    template <typename T, template <typename, class = std::allocator <T> > class ContainerT,
              class = typename std::enable_if<Internal::can_js_stringify<typename ContainerT<T>::value_type>::value>::type >
    std::string js_stringify(std::string const& name, ContainerT <T> values, StringificationOptions const& options = DEFAULT_OPTIONS,
                             typename std::enable_if<has_bidirectional_iterator<T, ContainerT>::value>::type* = nullptr)
    {
        return Internal::js_stringify_i(name, values, [](ContainerT <T> const& c){ auto end = c.end(); end--; return end;  });
    }
}

#endif // JSS_BIDIRECTIONAL_H_INCLUDED
