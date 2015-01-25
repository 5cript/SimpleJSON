#ifndef JSS_FUSION_VECTOR_H_INCLUDED
#define JSS_FUSION_VECTOR_H_INCLUDED

#include "jss_core.h"
#include "jss_tuple.h"

#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/vector.hpp>

namespace JSON
{
    /*
    template <typename ... Types>
    std::string js_stringify(std::initializer_list <std::string> const& names, boost::fusion::vector <Types...> values, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        std::deque <std::string> d_names {names.begin(), names.end()};
        std::vector <std::string> result;
        JS_Tuple::traverse_tuple<boost::fusion::vector> (values, result, d_names, options);
        return js_make_object(result);
    }

    template <template <typename, typename = std::allocator <std::string> > class NameContainerT, typename ... Types>
    std::string js_stringify(NameContainerT <std::string> const& names, boost::fusion::vector <Types...> values, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        return js_stringify <std::deque>(std::deque<std::string>{names}, values, options);
    }
    */
}

#endif // JSS_FUSION_VECTOR_H_INCLUDED
