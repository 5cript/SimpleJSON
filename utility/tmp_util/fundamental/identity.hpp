#pragma once

namespace mplex {
    template <typename T>
    struct identity {
        using type = T;
    };

    struct identity_functor {
        template <typename T>
        struct apply {
            using type = T;
        };
    };
}
