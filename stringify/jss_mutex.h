#ifndef JSS_MUTEX_H_INCLUDED
#define JSS_MUTEX_H_INCLUDED

#include "jss_core.h"
#include <mutex>

namespace JSON
{
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::mutex& value, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        /*
        WRITE_NAME(stream);
        stream << '"'
               << [&]() -> bool { bool v = value.try_lock(); if (v) value.unlock(); return v; }()
               << '"'
        ;
        */
        return stream;
    }
}

#endif // JSS_MUTEX_H_INCLUDED
