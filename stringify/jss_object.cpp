#include "jss_object.h"

namespace JSON
{
    std::string js_make_object(std::vector <std::string> const& elements, StringificationOptions const& options)
    {
        std::stringstream sstr;
        sstr << '{';
        if (!elements.empty())
        {
            std::copy(elements.begin(), elements.end() - 1, std::ostream_iterator<std::string>(sstr, options.delimiter.c_str()));
            sstr << elements.back();
        }
        sstr << '}';
        return sstr.str();
    }
}
