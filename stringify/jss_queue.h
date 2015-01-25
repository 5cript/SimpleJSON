#ifndef JSS_QUEUE_H_INCLUDED
#define JSS_QUEUE_H_INCLUDED

#include "jss_core.h"
#include "jss_deque.h"

#include <queue>
#include <deque>

// WARNING, THIS IS INEFFICIENT, USE A DEQUE INSTEAD!

namespace JSON
{
    template <typename T, template <typename, class = std::allocator <T> > class ContainerT = std::deque,
              class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    inline std::string js_stringify(std::string const& name, std::queue <T, ContainerT <T> > values, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        std::deque <T> dq;
        while (!values.empty())
        {
            if (options.reverse_order)
                dq.push_back(values.front());
            else
                dq.push_front(values.front());
            values.pop();
        }
        return js_stringify(name, dq, options);
    }
}

#endif // JSS_QUEUE_H_INCLUDED
