#ifndef RSS_VALARRY_H_INCLUDED
#define RSS_VALARRY_H_INCLUDED

// has no allocator and therefore is not compatible in jss_container
#include <valarray>

namespace JSON
{
    template <typename T>
    std::string js_stringify(std::string const& name, std::valarray <T> const& values, StringificationOptions const& options = DEFAULT_OPTIONS,
                             typename std::enable_if<Internal::can_js_stringify<T>::value>::type* = nullptr)
    {
        using namespace Internal;

        std::stringstream sstr;
        WRITE_ARRAY_START(sstr);
        if (values.size() != 0)
        {
            APPLY_IO_MANIPULATERS(sstr);
            auto noNameOption = options;
            noNameOption.ignore_name = true;
            for (auto i = std::begin(values); i != std::end(values) -1 ; ++i)
            {
                sstr << js_stringify({}, *i, noNameOption);
                sstr << options.delimiter;
            }
            sstr << js_stringify({}, *(std::end(values) - 1), noNameOption);
        }
        WRITE_ARRAY_END(sstr);
        return sstr.str();
    }
}

#endif // RSS_VALARRY_H_INCLUDED
