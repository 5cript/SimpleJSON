#ifndef JSS_OBJECT_H_INCLUDED
#define JSS_OBJECT_H_INCLUDED

#include "jss_core.h"
#include "jss_check.h"
#include <vector>
#include <string>

namespace JSON
{
    namespace Internal
    {
        template <typename Type,
                  class = typename std::enable_if <std::is_class <Type>::value>::type >
        class is_js_object
        {
            class yes { char m;};
            class no { yes m[2];};

            struct BaseMixin
            {
                std::string CLASS_STRINGIFY_FUNCTION_NAME(StringificationOptions){ return {}; }
            };
            struct Base : public Type, public BaseMixin {};

            template <typename T, T t>  class Helper{};

            template <typename U>
            static no deduce(U*, Helper<std::string (BaseMixin::*)(StringificationOptions), &U::CLASS_STRINGIFY_FUNCTION_NAME>* = 0);

            static yes deduce(...);
        public:
            static const bool value = sizeof(yes) == sizeof(deduce((Base*)(0)));
        };
    }

    namespace Internal
    {
        template <typename T,
                  class = typename std::enable_if<Internal::is_js_object<T>::value>::type >
        std::ostream& operator << (std::ostream& os, T const& object)
        {
            os << '{' << object.CLASS_STRINGIFY_FUNCTION_NAME(DEFAULT_OPTIONS) << '}';
            return os;
        }
    }

    template <typename T,
              class = typename std::enable_if<std::is_class<T>::value>::type,
              class = typename std::enable_if<Internal::is_js_object<T>::value>::type >
    std::string js_stringify(std::string const& name, T const& value, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        using namespace Internal;

        std::stringstream sstr;
        WRITE_NAME(sstr);

        //! if you get an error here, your provided js_stringify functions is not const
        //! or if you used BOOST_FUSION_ADAPT_STRUCT, your adaption is incorrect

        sstr << value;
        return sstr.str();
    }

    std::string js_make_object(std::vector <std::string> const& elements, StringificationOptions const& options = DEFAULT_OPTIONS);
}

#endif // JSS_OBJECT_H_INCLUDED
