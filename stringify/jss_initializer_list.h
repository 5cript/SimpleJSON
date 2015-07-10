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
    std::ostream& stringify (std::ostream& stream, std::initializer_list <std::string> const& names, std::initializer_list <T> values, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        std::vector <std::string> result;
        std::deque <std::string> d_names {names};
        int counter = 0;
        for (auto const& i : values)
        {
            if (!d_names.empty())
            {
                result.push_back(stringify(d_names.front(), i, options));
                d_names.pop_front();
            }
            else
            {
                result.push_back(stringify(std::string("_") + std::to_string(counter), i, options));
            }
            ++counter;
        }
        js_make_object(stream, result, options);
        return stream;
    }

    template <typename T>
    std::ostream& stringify (std::ostream& stream, std::initializer_list <_JS_STRING_PAIR<T>> pairs, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        std::vector <std::string> result;
        for (auto const& i : pairs)
        {
            result.push_back(stringify(i.name, i.value));
        }
        js_make_object(stream, result, options);
        return stream;
    }

    template <typename T>
    std::ostream& stringify (std::ostream& stream, std::string const& name, std::initializer_list <T> pairs, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        return stringify(name, std::vector<T> {pairs});
    }
}

#endif // JSS_INITIALIZER_LIST_H_INCLUDED
