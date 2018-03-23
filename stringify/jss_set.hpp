#pragma once

#include "jss_core.hpp"
#include <set>

namespace JSON
{
    template <typename KVT, typename CompareT = std::less <KVT>, class AllocT = std::allocator <KVT> >
    std::ostream& stringify (std::ostream& stream, std::string const& name, std::set<KVT, CompareT, AllocT> const& values, StringificationOptions options)
    {
        static_assert (!Internal::is_optional <KVT>::value, "A set of boost::optional is not allowed");
        using namespace Internal;

        SJSON_WRITE_ARRAY_START(stream);
        if (!values.empty())
        {
            options.ignore_name = true;
            auto bfe = values.end();
            bfe--;
            for (auto i = values.begin(); i != bfe; ++i)
            {
                stringify (stream, {}, *i, options);
                stream << options.delimiter;
            }
            stringify (stream, {}, *values.rbegin(), options);
        }
        SJSON_WRITE_ARRAY_END(stream);
        return stream;
    }

    template <typename KVT, typename CompareT = std::less <KVT>, class AllocT = std::allocator <KVT> >
    std::ostream& stringify (std::ostream& stream, std::string const& name, std::multiset<KVT, CompareT, AllocT> const& values, StringificationOptions options)
    {
        using namespace Internal;

        SJSON_WRITE_ARRAY_START(stream);
        options.ignore_name = true;

        bool first = true;
        for (auto const& i : values)
        {
            if (Internal::is_optional_set(i))
            {
                if (!first)
                    stream << options.delimiter;
                stringify(stream, {}, i, options);
                first = false;
            }
        }
        SJSON_WRITE_ARRAY_END(stream);
        return stream;
    }
}
