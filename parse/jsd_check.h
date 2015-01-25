#ifndef JSD_CHECK_H_INCLUDED
#define JSD_CHECK_H_INCLUDED

#include "jsd_core.h"

namespace JSON { namespace Internal {

    template<typename T>
    class can_js_parse
    {
        template<typename U>
        static char check(...);
        template<typename U>
        static char (&check(decltype(js_parse(std::declval<U>(), std::declval<std::string const>(), std::declval<PropertyTree const>(), std::declval<ParsingOptions const>()))*))[2];
        public:
        static const bool value=sizeof(check<T>(0))==2;
    };

}
}

#endif // JSD_CHECK_H_INCLUDED
