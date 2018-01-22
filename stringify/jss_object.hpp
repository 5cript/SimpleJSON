#pragma once

#include "jss_core.hpp"
#include "jss_check.hpp"
#include <vector>
#include <string>
#include <iostream>

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
                std::ostream& CLASS_STRINGIFY_FUNCTION_NAME(std::ostream& stream, StringificationOptions){ return stream; }
            };
            struct Base : public Type, public BaseMixin {};

            template <typename T, T>  class Helper{};

            template <typename U>
            static no deduce(U*, Helper<std::ostream& (BaseMixin::*)(std::ostream&, StringificationOptions), &U::CLASS_STRINGIFY_FUNCTION_NAME>* = nullptr);

            static yes deduce(...);
        public:
            static const bool value = sizeof(yes) == sizeof(deduce((Base*)(nullptr)));
        };
    }

    template <typename T,
              class = typename std::enable_if<std::is_class<T>::value>::type,
              class = typename std::enable_if<Internal::is_js_object<T>::value>::type >
    std::ostream& stringify(std::ostream& stream, std::string const& name, T const& value, StringificationOptions const& options = {})
    {
        using namespace Internal;

        WRITE_NAME(stream);

        //! if you get an error here, your provided stringify functions is not const
        //! or if you used BOOST_FUSION_ADAPT_STRUCT, your adaption is incorrect

        value.stringify(stream, options);
        return stream;
    }

    std::ostream& js_make_object(std::ostream& stream, std::vector <std::string> const& elements, StringificationOptions const& options = {});

    #define JSON_VERIFY_CLASS_VALIDITY(T) \
    static_assert (JSON::Internal::is_js_object <T>::value, "The class/struct is not a stringifiable struct, please check the function signature");
}
