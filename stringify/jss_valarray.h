#ifndef RSS_VALARRY_H_INCLUDED
#define RSS_VALARRY_H_INCLUDED

// has no allocator and therefore is not compatible in jss_container
#include <valarray>

namespace JSON
{
    template <typename T>
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::valarray <T> const& values, StringificationOptions const& options = DEFAULT_OPTIONS,
                            typename std::enable_if<Internal::can_stringify<T>::value>::type* = nullptr)
    {
        using namespace Internal;

        WRITE_ARRAY_START(stream);
        if (values.size() != 0)
        {
            APPLY_IO_MANIPULATERS(stream);
            auto noNameOption = options;
            noNameOption.ignore_name = true;
            for (auto i = std::begin(values); i != std::end(values) -1 ; ++i)
            {
                stringify(stream, {}, *i, noNameOption);
                stream << options.delimiter;
            }
            stream << stringify(stream, {}, *(std::end(values) - 1), noNameOption);
        }
        WRITE_ARRAY_END(stream);
        return stream;
    }
}

#endif // RSS_VALARRY_H_INCLUDED
