#ifndef JSS_CHECK_H_INCLUDED
#define JSS_CHECK_H_INCLUDED

#include "jss_core.hpp"
#include <sstream>
#include <utility>

namespace JSON { namespace Internal {

    class StreamMock : public std::ostream {};
    static StreamMock _smock;

    template <typename T>
    class can_stringify_1
    {
        template<typename U>
        static char check(...);
        template<typename U>
        static char (&check(decltype(stringify(std::declval<std::ostream&>(), std::declval<std::string const>(), std::declval<U>(), std::declval<StringificationOptions const>()))))[2];
        public:
        static const bool value = sizeof(check<T> (_smock)) == 2;
    };

    template <typename T>
    class can_stringify_2
    {
        template<typename U>
        static char check(...);
        template<typename U>
        static char (&check(decltype(stringify(std::declval<std::ostream&>(), std::declval<std::string const>(), std::declval<U>(), std::declval<StringificationOptions>()))))[2];
        public:
        static const bool value = sizeof(check<T> (_smock)) == 2;
    };

    template <typename T>
    struct can_stringify
    {
        static const bool value = can_stringify_1<T>::value || can_stringify_2<T>::value;
    };

}
}

#endif // JSS_CHECK_H_INCLUDED
