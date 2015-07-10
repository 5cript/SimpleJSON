#include "jss_options.h"

namespace JSON
{
    void IO_Options::apply(std::stringstream& ss) const
    {
        if (!enabled) return;

        ss << std::setfill(fill_char) << std::setbase(base);
        if (width != 0)
            ss << std::setw(width);
        ss << std::setiosflags(ioflags);
    }
    void IO_Options::apply(std::ostringstream& ss) const
    {
        if (!enabled) return;

        ss << std::setfill(fill_char) << std::setbase(base);
        if (width != 0)
            ss << std::setw(width);
        ss << std::setiosflags(ioflags);
    }
    void IO_Options::apply(std::ostream& ss) const
    {
        return;
    }
}
