#ifndef JSS_ITERATOR_H_INCLUDED
#define JSS_ITERATOR_H_INCLUDED

#include "jss_core.h"
#include "iterator_traits.h"
#include "jss_optional.h"

namespace JSON
{
    namespace Internal
    {
        template <typename T>
        class IteratorRange
        {
        public:
            IteratorRange(T a, T b) : first (a), second(b) {}

            inline T begin() const { return first; }
            inline T end() const { return second; }

        private:
            T first;
            T second;
        };
    }

    template <typename IteratorT>
    Internal::IteratorRange<IteratorT> make_range(IteratorT begin, IteratorT end)
    {
        return Internal::IteratorRange<IteratorT> (begin, end);
    }

    template <typename IteratorT,
              typename = typename std::enable_if <Internal::can_stringify<typename IteratorT::value_type>::value>::type >
    std::ostream& stringify (std::ostream& stream, const std::string& name, Internal::IteratorRange<IteratorT> const& range, StringificationOptions options = DEFAULT_OPTIONS,
                             typename std::enable_if <is_random_access_iterator<IteratorT>::value ||
                                                      is_bidirectional_iterator<IteratorT>::value ||
                                                      is_forward_iterator<IteratorT>::value>::type* = nullptr)
    {
        WRITE_ARRAY_START(stream);
        options.ignore_name = true;
        if (range.end() != range.begin())
        {
            auto e = range.end();
            auto i = range.begin();

            bool first = true;
            for (;i != e; ++i)
            {
                if (Internal::is_optional_set(*i))
                {
                    if (!first)
                        stream << options.delimiter;
                    stringify(stream, {}, *i, options);
                    first = false;
                }
            }
        }
        WRITE_ARRAY_END(stream);
        return stream;
    }
}

#endif // JSS_ITERATOR_H_INCLUDED
