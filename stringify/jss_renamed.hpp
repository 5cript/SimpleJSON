#ifndef JSS_RENAMED_H_INCLUDED
#define JSS_RENAMED_H_INCLUDED

#include "jss_core.hpp"

#include "../utility/rename.hpp"

namespace JSON
{
    template <typename T, typename Name>
    std::ostream& stringify(std::ostream& stream, std::string const&, rename <T, Name> const& value, StringificationOptions options = DEFAULT_OPTIONS)
    {
        constexpr const auto name = Name::c_str;
        WRITE_NAME(stream);
        options.ignore_name = true;
        return JSON::stringify(stream, name, value.getValue(), options);
    }
}

#endif // JSS_RENAMED_H_INCLUDED
