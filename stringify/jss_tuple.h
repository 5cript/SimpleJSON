#ifndef JSS_TUPLE_H_INCLUDED
#define JSS_TUPLE_H_INCLUDED

#include "jss_core.h"
#include "jss_object.h"
#include <tuple>
#include <deque>
#include <initializer_list>

// note: you can use the overloads to specify names for each object of the tuple

namespace JSON
{
    namespace JS_Tuple {
        template <template <typename ...> class TupleType, std::size_t counter = 0, typename ... Types>
        inline typename std::enable_if<counter == sizeof...(Types), void>::type
        traverse_tuple(TupleType <Types...>&, std::vector <std::string>& result, std::deque <std::string>&, StringificationOptions const&) {}

        template <template <typename ...> class TupleType, std::size_t counter = 0, typename ... Types>
        inline typename std::enable_if<counter < sizeof...(Types), void>::type
        traverse_tuple(TupleType <Types...>& tuple, std::vector <std::string>& result, std::deque <std::string>& names, StringificationOptions const& options)
        {
            if (!names.empty())
            {
                result.push_back(js_stringify(names.front(), std::get<counter>(tuple), options));
                names.pop_front();
            }
            else
            {
                result.push_back(js_stringify(std::string("_") + std::to_string(counter), std::get<counter>(tuple), options));
            }
            traverse_tuple <TupleType, counter + 1, Types...>(tuple, result, names, options);
        }
    }

    template <template <typename, typename = std::allocator <std::string> > class NameContainerT, typename ... Types>
    std::string js_stringify(std::string const& name, NameContainerT <std::string> const& names, std::tuple <Types...> values, StringificationOptions options = DEFAULT_OPTIONS)
    {
        std::deque <std::string> d_names {names.begin(), names.end()};
        std::vector <std::string> result;
        options.ignore_name = false;
        options.in_object = true;
        JS_Tuple::traverse_tuple<std::tuple> (values, result, d_names, options);
        return js_make_object(result);
    }

    template <typename ... Types>
    std::string js_stringify(std::string const& name, std::initializer_list <std::string> const& names, std::tuple <Types...> values, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        return js_stringify <std::deque>(name, std::deque<std::string>{names}, values, options);
    }

    // for classes and checkings
    template <typename ... Types>
    std::string js_stringify(std::string const& name, std::tuple <Types...> values, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        return js_stringify(name, {}, values, options);
    }
}

#endif // JSS_TUPLE_H_INCLUDED
