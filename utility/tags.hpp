#pragma once

#include "tmp_util/control/if.hpp"
#include "tmp_util/functional/lift.hpp"

namespace JSON
{
    template <typename... Tags>
    struct Tag
    {
        using json_tags = Tag<Tags...>;
    };

    struct RootObject;

    template <typename...>
    struct always_false
    {
        static constexpr const bool value = false;
        using type = false_;
    };

    template <typename...>
    struct always_true
    {
        static constexpr const bool value = true;
        using type = true_;
    };

    template<typename T>
    struct void_ { typedef void type; };

    template <typename Obj, typename Tag, typename = void>
    struct contains_any_tag
    {
        static constexpr const bool value = false;
        using vt = false_;
        using type = void;
    };

    template <typename Obj, typename Tag>
    struct contains_any_tag <Obj, Tag, typename void_<typename Obj::json_tags>::type>
    {
        static constexpr const bool value = true;
        using vt = true_;
        using type = typename Obj::json_tags;
    };

    template <typename T>
    struct identity : public T {};

    template <typename What, typename T, typename... List>
    struct find
    {
        using lifted = lift <find>;
        using true_lift = lift <always_true>;
        using type = lazy_if_t<
            bool_ <std::is_same <What, T>::value>,
            then_ <true_lift>,
            else_ <lifted, What, List...>
        >;
    };

    template <typename What, typename T>
    struct find <What, T>
    {
        using true_lift = lift <always_true>;
        using false_lift = lift <always_false>;
        using type = lazy_if_t <
            bool_ <std::is_same <What, T>::value>,
            then_ <true_lift>,
            else_ <false_lift>
        >;
    };

    template <typename What, typename Obj>
    struct contains_tag_impl
    {
        using type = lift <always_false>;
    };

    template <typename What, typename... List>
    struct contains_tag_impl <What, Tag <List...>>
    {
        using type = typename find <What, List...>::type;
    };

    template <typename Obj, typename What>
    struct contains_tag
    {
        using tag_check = contains_any_tag <Obj, What>;

        using impl_lift = lift <contains_tag_impl>;
        using false_lift = lift <always_false>;

        using type = lazy_if_t <
            typename tag_check::vt,
            then_ <impl_lift, What, typename tag_check::type>,
            else_ <false_lift>
        >;

        constexpr static const bool value = type::template apply<>::value;
    };
}
