#ifndef JSS_CONTAINER_H_INCLUDED
#define JSS_CONTAINER_H_INCLUDED

#include "jss_core.h"
#include "jss_object.h"
#include "jss_check.h"
#include <functional>

namespace JSON { namespace Internal
{
    template <typename T, template <typename, class = std::allocator <T> > class ContainerT,
              typename FuncT = std::function <typename ContainerT<T>::const_iterator(ContainerT<T> const&)>,
              class = typename std::enable_if<Internal::can_stringify<typename ContainerT<T>::value_type>::value>::type >
    inline std::ostream& stringify_i(std::ostream& stream, std::string const& name, ContainerT <T> const& values, FuncT end_iter, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        using namespace Internal;

        WRITE_ARRAY_START(stream);
        if (!values.empty())
        {
            auto end = end_iter(values);
            APPLY_IO_MANIPULATERS(stream);
            auto noNameOption = options;
            noNameOption.ignore_name = true;
            auto i = values.begin();
            for (; i != end; ++i)
            {
                stringify(stream, {}, *i, noNameOption);
                stream << options.delimiter;
            }
            stringify(stream, {}, *i, noNameOption);
        }
        WRITE_ARRAY_END(stream);
        return stream;
    }
} // Internal
} // JSON

#endif // JSS_CONTAINER_H_INCLUDED
