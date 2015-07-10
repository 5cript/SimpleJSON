#ifndef JSS_SET_H_INCLUDED
#define JSS_SET_H_INCLUDED

#include "jss_core.h"
#include <set>

namespace JSON
{
    template <typename KVT, typename CompareT = std::less <KVT>, class AllocT = std::allocator <KVT> >
    std::ostream& stringify (std::ostream& stream, std::string const& name, std::set<KVT, CompareT, AllocT> const& values, StringificationOptions options)
    {
        using namespace Internal;

        WRITE_ARRAY_START(stream);
        if (!values.empty())
        {
            options.ignore_name = true;
            APPLY_IO_MANIPULATERS(stream);
            auto bfe = values.end();
            bfe--;
            for (auto i = values.begin(); i != bfe; ++i)
            {
                stringify (stream, {}, *i, options);
                stream << options.delimiter;
            }
            stringify (stream, {}, *values.rbegin(), options);
        }
        WRITE_ARRAY_END(stream);
        return stream;
    }

    template <typename KVT, typename CompareT = std::less <KVT>, class AllocT = std::allocator <KVT> >
    std::ostream& stringify (std::ostream& stream, std::string const& name, std::multiset<KVT, CompareT, AllocT> const& values, StringificationOptions options)
    {
        using namespace Internal;

        WRITE_ARRAY_START(stream);
        if (!values.empty())
        {
            options.ignore_name = true;
            APPLY_IO_MANIPULATERS(stream);
            auto bfe = values.end();
            bfe--;
            for (auto i = values.begin(); i != bfe; ++i)
            {
                stringify (stream, {}, *i, options);
                stream << options.delimiter;
            }
            stringify (stream, {}, *values.rbegin(), options);
        }
        WRITE_ARRAY_END(stream);
        return stream;
    }
}

#endif // JSS_SET_H_INCLUDED
