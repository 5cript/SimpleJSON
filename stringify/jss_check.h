#ifndef JSS_CHECK_H_INCLUDED
#define JSS_CHECK_H_INCLUDED

#include "jss_core.h"

namespace JSON { namespace Internal {

    template<typename T>
    class can_js_stringify_1
    {
        template<typename U>
        static char check(...);
        template<typename U>
        static char (&check(decltype(js_stringify(std::declval<std::string const>(), std::declval<U>(), std::declval<StringificationOptions const>()))*))[2];
        public:
        static const bool value=sizeof(check<T>(0))==2;
    };

    template<typename T>
    class can_js_stringify_2
    {
        template<typename U>
        static char check(...);
        template<typename U>
        static char (&check(decltype(js_stringify(std::declval<std::string const>(), std::declval<U>(), std::declval<StringificationOptions>()))*))[2];
        public:
        static const bool value=sizeof(check<T>(0))==2;
    };

    template<typename T>
    struct can_js_stringify
    {
        static const bool value = can_js_stringify_1<T>::value || can_js_stringify_2<T>::value;
    };

}
}

#endif // JSS_CHECK_H_INCLUDED
