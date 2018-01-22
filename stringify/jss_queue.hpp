#pragma once

#include "jss_core.hpp"
#include "jss_deque.hpp"

#include <queue>
#include <deque>

// WARNING, THIS IS INEFFICIENT, USE A DEQUE INSTEAD!

namespace JSON
{
    template <typename T, template <typename, class = std::allocator <T> > class ContainerT = std::deque,
              class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::queue <T, ContainerT <T> > values, StringificationOptions const& options = {})
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
        stringify(stream, name, dq, options);
        return stream;
    }
}
