#pragma once

#include <iomanip>
#include <string>
#include <sstream>

namespace JSON
{
    enum class PointerHandling : int
    {
        IGNORE_POINTERS, // Default
        DEREFERENCE, // derefences until it is not a pointer anymore
        ADDRESS
    };

    struct StringificationOptions
    {
        bool ignore_name;
        std::string delimiter;
        bool reverse_order;
        PointerHandling ptr_behaviour;
        bool in_object;

        StringificationOptions (bool ignore_name = false,
                                std::string delimiter = ",",
                                bool reverse_order = false,
                                PointerHandling ptr_behaviour = {},
                                bool in_object = false)
            : ignore_name {ignore_name}
            , delimiter {delimiter}
            , reverse_order {reverse_order}
            , ptr_behaviour {ptr_behaviour}
            , in_object {in_object}
        {}
    };

    #define DEFAULT_OPTIONS StringificationOptions{}

    static auto const ProduceNamedOutput = StringificationOptions{false, ",", false, {}, true};
}
