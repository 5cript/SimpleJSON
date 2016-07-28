#pragma once

namespace JSON
{
    template <typename...>
    struct pack
    {
        using type = pack;
    };

    template <unsigned I, typename Pack>
    struct pack_element
    {
        using type = typename pack_element <I - 1, Pack>::type;
    };

    template <typename Head, typename... Tail>
    struct pack_element <0, pack <Head, Tail...>>
    {
        using type = Head;
    };

    template <typename T>
    struct pack_front
    {
    };

    template <typename Head, typename... Tail>
    struct pack_front <pack <Head, Tail...>>
    {
        using type = Head;
    };
}
