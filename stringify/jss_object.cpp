#include "jss_object.h"

namespace JSON
{
    std::ostream& js_make_object (std::ostream& stream, std::vector <std::string> const& elements, StringificationOptions const& options)
    {
        stream << '{';
        if (!elements.empty())
        {
            std::copy (elements.begin(), elements.end() - 1, std::ostream_iterator<std::string>(stream, options.delimiter.c_str()));
            stream << elements.back();
        }
        stream << '}';
        return stream;
    }
}
