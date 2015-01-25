#ifndef JSS_SET_H_INCLUDED
#define JSS_SET_H_INCLUDED

#include "jss_core.h"
#include <set>

namespace JSON
{
    template <typename KVT, typename CompareT = std::less <KVT>, class AllocT = std::allocator <KVT> >
    std::string js_stringify(std::string const& name, std::set<KVT, CompareT, AllocT> const& values, StringificationOptions options)
    {
        using namespace Internal;

        std::stringstream sstr;
        WRITE_ARRAY_START(sstr);
        if (!values.empty())
        {
            options.ignore_name = true;
            APPLY_IO_MANIPULATERS(sstr);
            auto bfe = values.end();
            bfe--;
            for (auto i = values.begin(); i != bfe; ++i)
            {
                sstr << js_stringify({}, *i, options);
                sstr << options.delimiter;
            }
            sstr << js_stringify({}, *values.rbegin(), options);
        }
        WRITE_ARRAY_END(sstr);
        return sstr.str();
    }

    template <typename KVT, typename CompareT = std::less <KVT>, class AllocT = std::allocator <KVT> >
    std::string js_stringify(std::string const& name, std::multiset<KVT, CompareT, AllocT> const& values, StringificationOptions options)
    {
        using namespace Internal;

        std::stringstream sstr;
        WRITE_ARRAY_START(sstr);
        if (!values.empty())
        {
            options.ignore_name = true;
            APPLY_IO_MANIPULATERS(sstr);
            auto bfe = values.end();
            bfe--;
            for (auto i = values.begin(); i != bfe; ++i)
            {
                sstr << js_stringify({}, *i, options);
                sstr << options.delimiter;
            }
            sstr << js_stringify({}, *values.rbegin(), options);
        }
        WRITE_ARRAY_END(sstr);
        return sstr.str();
    }
}

#endif // JSS_SET_H_INCLUDED
