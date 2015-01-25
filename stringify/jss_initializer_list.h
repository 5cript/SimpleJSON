#ifndef JSS_INITIALIZER_LIST_H_INCLUDED
#define JSS_INITIALIZER_LIST_H_INCLUDED

#include "jss_core.h"
#include "jss_object.h"

#include <initializer_list>
#include <deque>
#include <vector>

namespace JSON
{
    template <typename T>
    struct _JS_STRING_PAIR
    {
        std::string name;
        T value;
    };

    template <typename T>
    _JS_STRING_PAIR<T> _make_JS_STRING_PAIR (std::string name, T value)
    {
        return _JS_STRING_PAIR<T> {name, value};
    }

    template <typename T>
    std::string js_stringify(std::initializer_list <std::string> const& names, std::initializer_list <T> values, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        std::vector <std::string> result;
        std::deque <std::string> d_names {names};
        int counter = 0;
        for (auto const& i : values)
        {
            if (!d_names.empty())
            {
                result.push_back(js_stringify(d_names.front(), i, options));
                d_names.pop_front();
            }
            else
            {
                result.push_back(js_stringify(std::string("_") + std::to_string(counter), i, options));
            }
            ++counter;
        }
        return js_make_object(result, options);
    }

    template <typename T>
    std::string js_stringify(std::initializer_list <_JS_STRING_PAIR<T>> pairs, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        std::vector <std::string> result;
        for (auto const& i : pairs)
        {
            result.push_back(js_stringify(i.name, i.value));
        }
        return js_make_object(result, options);
    }

    template <typename T>
    std::string js_stringify(std::string const& name, std::initializer_list <T> pairs, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        return js_stringify(name, std::vector<T> {pairs});
    }
}

#endif // JSS_INITIALIZER_LIST_H_INCLUDED
