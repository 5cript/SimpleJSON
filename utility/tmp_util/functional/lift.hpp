#pragma once

namespace JSON
{
    template <template <typename...> class T>
    struct lift {
        template <typename... Params>
        struct apply
            : public T <Params...>
        {
        };
    };
}
