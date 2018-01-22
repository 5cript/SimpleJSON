#pragma once

#include "jss_core.hpp"
#include <mutex>

namespace JSON
{
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::mutex& value, StringificationOptions const& options = {})
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
