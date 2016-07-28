#pragma once

#include "jsd_core.hpp"

namespace JSON { namespace Internal {

    template<typename T>
    class can_parse
    {
        template<typename U>
        static char check(...);
        template<typename U>
        static char (&check(decltype(parse(std::declval<U>(), std::declval<std::string const>(), std::declval<PropertyTree const>(), std::declval<ParsingOptions const>()))*))[2];
        public:
        static const bool value=sizeof(check<T>(0))==2;
    };

}
}
