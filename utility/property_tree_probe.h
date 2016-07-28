#pragma once

#include <iosfwd>

namespace JSON
{
    struct tree_probe
    {
    };

    inline std::istream& operator>>(std::istream& istream, tree_probe const&)
    {
        // ignore.
        return istream;
    }
}
