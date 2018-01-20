#pragma once

#include "../fundamental/eval_if.hpp"
#include "../fundamental/integral.hpp"

namespace JSON
{
    template <typename Condition,
              typename TrueT,
              typename FalseT>
    struct if_ {
        using type = TrueT;
    };

    template <typename TrueT,
              typename FalseT>
    struct if_ <bool_ <false>, TrueT, FalseT> {
        using type = FalseT;
    };

    template <typename IntegralT,
              typename TrueT,
              typename FalseT>
    struct if_ <integral <IntegralT, 0>, TrueT, FalseT> {
        using type = FalseT;
    };

    template <typename Condition, typename TrueT, typename FalseT>
    using if_t = typename if_ <Condition, TrueT, FalseT>::type;

    template <bool Condition, typename TrueT, typename FalseT>
    using if_vt = typename if_ <bool_ <Condition>, TrueT, FalseT>::type;

//----------------------------------------------------------------------------------------------------------

    template <typename Function, typename... Parameters>
    struct then_ {
        template <typename Condition>
        struct apply {
            using type = eval_if_default_t <bool_ <Condition::value && sizeof...(Parameters) != 0>, Function, Function, Parameters...>;
        };
    };

    template <typename Function, typename... Parameters>
    struct else_ {
        template <typename Condition>
        struct apply {
            using type = eval_if_default_t <bool_ <!Condition::value && sizeof...(Parameters) != 0>, Function, Function, Parameters...>;
        };
    };

    template <typename Condition, typename Then, typename Else>
    struct lazy_if {
        using type = typename Then::template apply <true_>::type;
    };

    template <typename Then, typename Else>
    struct lazy_if <false_, Then, Else> {
        using type = typename Else::template apply <false_>::type;
    };

    template <typename IntegralT, typename Then, typename Else>
    struct lazy_if <integral <IntegralT, 0>, Then, Else> {
        using type = typename Else::template apply <false_>::type;
    };

    template <typename Condition, typename Then, typename Else>
    using lazy_if_t = typename lazy_if <Condition, Then, Else>::type;

    template <bool Condition, typename Then, typename Else>
    using lazy_if_vt = typename lazy_if <bool_ <Condition>, Then, Else>::type;
}
