#pragma once

#include "jss_core.hpp"
#include "../utility/tmp_util/type_of_size.hpp"

#include <type_traits>

namespace JSON
{
    template <typename T>
    std::ostream& stringify(std::ostream& stream,
                            std::string const& name,
                            T value,
                            StringificationOptions const& options = {},
                            typename std::enable_if <std::is_enum <T>::value>::type* = nullptr)
    {
        WRITE_NAME(stream);
        stream << static_cast <typename type_of_size <sizeof(T) * 8>::type> (value);
        return stream;
    }
}
