#pragma once

#include "jss_core.hpp"
#include "jss_object.hpp"
#include "jss_check.hpp"
#include "jss_optional.hpp"
#include "../utility/optional_info.hpp"
#include <functional>

namespace JSON { namespace Internal
{
    template <typename T, template <typename, class = std::allocator <T> > class ContainerT,
              typename FuncT = std::function <typename ContainerT<T>::const_iterator(ContainerT<T> const&)>,
              class = typename std::enable_if<Internal::can_stringify<typename ContainerT<T>::value_type>::value>::type >
    inline std::ostream& stringify_i(std::ostream& stream, std::string const& name, ContainerT <T> const& values, StringificationOptions const& options = {})
    {
        using namespace Internal;

        SJSON_WRITE_ARRAY_START(stream);
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
        SJSON_WRITE_ARRAY_END(stream);
        return stream;
    }
} // Internal
} // JSON
