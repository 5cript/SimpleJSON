#pragma once

#include "jss_core.hpp"
#include "jss_object.hpp"
#include "jss_optional.hpp"

#include <tuple>
#include <deque>
#include <initializer_list>
#include <sstream>

// note: you can use the overloads to specify names for each object of the tuple

namespace JSON
{
    namespace JS_Tuple {
        template <template <typename ...> class TupleType, std::size_t counter = 0, typename ... Types>
        inline typename std::enable_if<counter == sizeof...(Types), void>::type
        traverse_tuple(TupleType <Types...>&, std::vector <std::string>&, std::deque <std::string>&, StringificationOptions const&) {}

        template <template <typename ...> class TupleType, std::size_t counter = 0, typename ... Types>
        inline typename std::enable_if<counter < sizeof...(Types), void>::type
        traverse_tuple(TupleType <Types...>& tuple, std::vector <std::string>& result, std::deque <std::string>& names, StringificationOptions const& options)
        {
            static_assert (!Internal::is_optional <typename std::tuple_element <counter, TupleType<Types...>>::type>::value, "A tuple may not contain boost::optional types");

            if (!names.empty())
            {
                std::stringstream sstr;
                stringify(sstr, names.front(), std::get<counter>(tuple), options);
                result.push_back(sstr.str());
                names.pop_front();
            }
            else
            {
                std::stringstream sstr;
                stringify(sstr, std::string("_") + std::to_string(counter), std::get<counter>(tuple), options);
                result.push_back(sstr.str());
            }
            traverse_tuple <TupleType, counter + 1, Types...>(tuple, result, names, options);
        }
    }

    template <template <typename, typename = std::allocator <std::string> > class NameContainerT, typename ... Types>
    std::ostream& stringify (std::ostream& stream, std::string const& name, NameContainerT <std::string> const& names, std::tuple <Types...> values, StringificationOptions options = {})
    {
        std::deque <std::string> d_names {names.begin(), names.end()};
        std::vector <std::string> result;
        options.ignore_name = false;
        options.in_object = true;
        JS_Tuple::traverse_tuple<std::tuple> (values, result, d_names, options);
        SJSON_WRITE_NAME(stream);
        return js_make_object(stream, result);
    }

    template <typename ... Types>
    std::ostream& stringify (std::ostream& stream, std::string const& name, std::initializer_list <std::string> const& names, std::tuple <Types...> values, StringificationOptions const& options = {})
    {
        return stringify <std::deque>(stream, name, std::deque<std::string>{names}, values, options);
    }

    // for classes and checkings
    template <typename ... Types>
    std::ostream& stringify (std::ostream& stream, std::string const& name, std::tuple <Types...> values, StringificationOptions const& options = {})
    {
        return stringify(stream, name, {}, values, options);
    }
}
