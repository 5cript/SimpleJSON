#ifndef JSS_OPTIONS_H_INCLUDED
#define JSS_OPTIONS_H_INCLUDED

#include <iomanip>
#include <string>
#include <sstream>

namespace JSON
{
    enum class PointerHandling : int
    {
        IGNORE, // Default
        DEREFERENCE, // derefences until it is not a pointer anymore
        ADDRESS
    };

    struct IO_Options
    {
        bool enabled;
        int width; // std::setw
        std::stringstream::char_type fill_char; // std::setfill
        int base; // std::setbase
        std::ios_base::fmtflags ioflags; // std::setioflags

        IO_Options (bool enabled = false, int width = 0, std::stringstream::char_type fill_char = ' ', int base = 10, std::ios_base::fmtflags ioflags = {})
            : enabled {enabled}
            , width {width}
            , fill_char {fill_char}
            , base {base}
            , ioflags {ioflags}
        { }

        void apply(std::ostream& ss) const;
        void apply(std::stringstream& ss) const;
        void apply(std::ostringstream& ss) const;
    };

    struct StringificationOptions
    {
        bool ignore_name;
        std::string delimiter;
        bool reverse_order;
        PointerHandling ptr_behaviour;
        IO_Options io_options;
        bool in_object;

        StringificationOptions (bool ignore_name = false, std::string delimiter = ",", bool reverse_order = false, PointerHandling ptr_behaviour = {}, IO_Options io_options = {})
            : ignore_name {ignore_name}
            , delimiter {delimiter}
            , reverse_order {reverse_order}
            , ptr_behaviour {ptr_behaviour}
            , io_options {io_options}
            , in_object {false}
        {}
    };

    #define DEFAULT_OPTIONS StringificationOptions{}
}

#endif // JSS_OPTIONS_H_INCLUDED
