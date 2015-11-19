#ifndef JSS_CONTAINER_H_INCLUDED
#define JSS_CONTAINER_H_INCLUDED

#include "jss_core.h"
#include "jss_object.h"
#include "jss_check.h"
#include "jss_optional.h"
#include <functional>

namespace JSON { namespace Internal
{
    template <typename T, template <typename, class = std::allocator <T> > class ContainerT,
              typename FuncT = std::function <typename ContainerT<T>::const_iterator(ContainerT<T> const&)>,
              class = typename std::enable_if<Internal::can_stringify<typename ContainerT<T>::value_type>::value>::type >
    inline std::ostream& stringify_i(std::ostream& stream, std::string const& name, ContainerT <T> const& values, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        using namespace Internal;

        WRITE_ARRAY_START(stream);
        auto noNameOption = options;
        noNameOption.ignore_name = true;

        bool first = true;
        for (auto const& i : values)
        {
            if (Internal::is_optional_set(i))
            {
                if (!first)
                    stream << options.delimiter;
                stringify(stream, {}, i, noNameOption);
                first = false;
            }
        }
        WRITE_ARRAY_END(stream);
        return stream;
    }
} // Internal
} // JSON

#endif // JSS_CONTAINER_H_INCLUDED
