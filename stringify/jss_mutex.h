#ifndef JSS_MUTEX_H_INCLUDED
#define JSS_MUTEX_H_INCLUDED

#include "jss_core.h"
#include <mutex>

namespace JSON
{
    std::string js_stringify(std::string const& name, std::mutex& value, StringificationOptions const& options = DEFAULT_OPTIONS)
    {
        std::stringstream sstr;
        WRITE_NAME(sstr);
        sstr << '"'
             << [&]() -> bool { bool v = value.try_lock(); if (v) value.unlock(); return v; }()
             << '"'
        ;
        return sstr.str();
    }
}

#endif // JSS_MUTEX_H_INCLUDED
