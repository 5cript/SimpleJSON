#ifndef JSS_STACK_H_INCLUDED
#define JSS_STACK_H_INCLUDED

#include "jss_core.h"
#include "jss_deque.h"

#include <stack>
#include <deque>

// WARNING, THIS IS INEFFICIENT, USE A DEQUE INSTEAD!

namespace JSON
{
    template <typename T, template <typename, class = std::allocator <T> > class ContainerT = std::deque,
              class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::stack <T, ContainerT <T> > values, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        std::deque <T> dq;
        while (!values.empty())
        {
            if (options.reverse_order)
                dq.push_back(values.top());
            else
                dq.push_front(values.top());
            values.pop();
        }
        return stringify(stream, name, dq, options);
    }
}

#endif // JSS_STACK_H_INCLUDED
