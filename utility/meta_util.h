#ifndef UTILITY_META_UTIL_H_INCLUDED
#define UTILITY_META_UTIL_H_INCLUDED

#include <type_traits>

namespace JSON
{
    namespace internal
    {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PACK
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename...>
        struct pack {};

        template <typename Pack>
        struct pack_size;

        template <typename... List>
        struct pack_size <pack <List...>> {
            enum {
                value = sizeof...(List)
            };
        };

        template <std::size_t Index, typename Pack>
        struct pack_element;

        template <typename Head, typename... Tail>
        struct pack_element <0, pack <Head, Tail...>> {
            using type = Head;
        };

        template <std::size_t Index, typename Head, typename... Tail>
        struct pack_element <Index, pack <Head, Tail...>>
            : pack_element <Index-1, pack <Tail...>>
        {
        };

        template <typename, typename>
        struct concat
        { };

        template <typename ... Ts, typename ... Us>
        struct concat <pack <Ts...>, pack <Us...>> {
            using type = pack <Ts..., Us...>;
        };

        template <typename T, typename U>
        using concat_t = typename concat <T, U>::type;

        template <typename Pack>
        struct pop_back
        { };

        template <>
        struct pop_back <pack <>> {
            using type = pack <>;
        };

        template <typename T>
        struct pop_back <pack <T>> {
            using type = pack <>;
        };

        template <typename T, typename ... List>
        struct pop_back <pack <T, List...>> {
            using type = concat_t <pack <T>, typename pop_back <pack <List...>>::type>;
        };

        template <typename Pack>
        using pop_back_t = typename pop_back <Pack>::type;

        template <typename Pack, template <typename...> class Function>
        struct apply {    };

        template <template <typename...> class Function, typename... List>
        struct apply <pack <List...>, Function> {
            using type = Function <List...>;
        };

        template <typename Pack, template <typename...> class Function>
        using apply_t = typename apply <Pack, Function>::type;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRIM
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename Pack, template <typename> class Predicate, bool Abort = false>
        struct trim_right {
            // Abort == false
            using type = typename std::conditional <Predicate<typename pack_element <pack_size <Pack>::value - 1, Pack>::type>::value,
                                                    typename trim_right <pop_back_t<Pack>, Predicate>::type,
                                                    Pack>::type;
        };

        template <typename Pack, template <typename> class Predicate>
        struct trim_right <Pack, Predicate, true> {
            using type = Pack;
        };

        template <template <typename> class Predicate>
        struct trim_right <pack <>, Predicate, false> {
            using type = pack <>;
        };

        template <typename Pack, template <typename> class Predicate>
        using trim_right_t = typename trim_right <Pack, Predicate>::type;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CEXPR_STRING
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <char C>
        using char_ = std::integral_constant <char, C>;

        template <typename... List>
        struct cexpr_string
        {
            using size_type = std::make_signed_t <std::size_t>;

            using type = pack <List...>;
            constexpr static const size_type size = sizeof...(List);
            constexpr static const size_type length = size;

            template <size_type N>
            struct at {
                static_assert(N < size, "Index out of bounds");

                constexpr static const char value = pack_element <N, type>::type::value;
                using type = typename pack_element <N, type>::type;
            };

            template <size_type N>
            using at_t = typename at <N>::type;

            constexpr static const char c_str[] = {
                List::value..., '\0'
            };

            constexpr static const size_type npos = -1;
        };

        template <typename... List>
        constexpr const char cexpr_string <List...>::c_str[];

        template <typename Char>
        struct is_zero {
            constexpr static const bool value = (Char::value == 0);
        };

        #define SPLIT_1(s, x)    JSON::internal::char_<( x < sizeof(s) ? s[x] : '\0' )>
        #define SPLIT_4(s, x)    SPLIT_1  (s, x), SPLIT_1  (s, x+1)  , SPLIT_1  (s, x+2)  , SPLIT_1  (s, x+3)
        #define SPLIT_16(s, x)   SPLIT_4  (s, x), SPLIT_4  (s, x+4)  , SPLIT_4  (s, x+8)  , SPLIT_4  (s, x+12)
        #define SPLIT_64(s, x)   SPLIT_16 (s, x), SPLIT_16 (s, x+16) , SPLIT_16 (s, x+32) , SPLIT_16 (s, x+48)
        #define SPLIT_256(s, x)  SPLIT_64 (s, x), SPLIT_64 (s, x+64) , SPLIT_64 (s, x+128) , SPLIT_64 (s, x+194)
        #define SPLIT_1024(s, x) SPLIT_256(s, x), SPLIT_256(s, x+256), SPLIT_256(s, x+512), SPLIT_256(s, x+768)

        #define STRING_IMPL(str, n) JSON::internal::apply_t <JSON::internal::trim_right_t <JSON::internal::pack <SPLIT_##n(str, 0)>, JSON::internal::is_zero>, JSON::internal::cexpr_string>

        #define SHORT_STRING(str) STRING_IMPL(str, 16)
        #define STRING(str) STRING_IMPL(str, 64)
        #define LONG_STRING(str) STRING_IMPL(str, 256) // HEAVY
        #define LONG_LONG_STRING(str) STRING_IMPL(str, 1024) // ULTRA HEAVY
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }


}


#endif // UTILITY_META_UTIL_H_INCLUDED
