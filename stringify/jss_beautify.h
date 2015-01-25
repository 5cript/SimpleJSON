#ifndef JSS_BEAUTIFY_H
#define JSS_BEAUTIFY_H

#include <string>
#include <sstream>

namespace JSON
{
    std::string js_beautify(std::string const& str, int pretab = 0);
}

#endif // JSS_BEAUTIFY_H

