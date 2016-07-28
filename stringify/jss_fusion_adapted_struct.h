#ifndef JSS_FUSION_ADAPTED_STRUCT_H_INCLUDED
#define JSS_FUSION_ADAPTED_STRUCT_H_INCLUDED

#include "jss_core.h"

#ifndef JSS_OBJECT_H_INCLUDED
#   include "jss_object.h"
#endif

#include "jss_optional.h"
#include "../utility/polymorphy.h"

#include <iostream>
#include <type_traits>

#include <boost/fusion/mpl.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/fusion/include/size.hpp>

namespace JSON
{
    namespace internal
    {
        template <typename Base, typename Derived, bool Enable = !std::is_same <Base, Derived>::value>
        struct Polify
        {
        };

        template <typename Base, typename Derived>
        struct Polify <Base, Derived, false>
        {
            template <typename... List>
            static void exec(List&...)
            {
                // not enabled
            }
        };

        template <typename Base, typename Derived>
        struct Polify <Base, Derived, true>
        {
            static void exec(std::ostream& stream, bool& first, Derived const& object)
            {
                using polydecl_type = polydecls <Base>;
                if (std::is_same <typename polydecl_type::type, no_poly>::value == false)
                {
                    // leave polymorphy mark behind
                    stream << "\"__cxx_type\": \"" << polydecl_type::identify_type(&object) << "\"";
                    first = false;
                }
            }
        };
    }

    template <typename T, typename Base = T>
    class AdaptedStringifier
    {
    public:
        std::ostream& operator()(std::ostream& stream, T const& object, StringificationOptions const& options) const
        {
            //! If you get an Error here, you likely forgot to use BOOST_FUSION_ADAPT_STRUCT / BOOST_FUSION_DECLARE_STRUCT !

            typedef boost::mpl::range_c<
                int,
                0,
                boost::fusion::result_of::size<T>::type::value
            > range;

            bool first = true;

            stream << '{';
            internal::Polify <Base, T>::exec(stream, first, object);
            boost::mpl::for_each<range> (std::bind<void>(_helper(boost::fusion::result_of::size<T>::type::value), std::placeholders::_1, std::ref(stream), std::ref(first), std::ref(object), std::ref(options)));
            stream << '}';
            return stream;
        }
    private:
        class _helper
        {
        public:
            template<class Index>
            void operator()(Index, std::ostream& os, bool& first, T const& object, StringificationOptions const& options) const
            {
                auto const& member = boost::fusion::at<Index>(object);
                if (Internal::is_optional_set(member))
                {
                    if (!first)
                        os << options.delimiter;
                    stringify(os, boost::fusion::extension::struct_member_name<T, Index::value>::call(), member, options);
                    first = false;
                }
            }
            _helper(int len) : len(len) {}
        private:
            int len;
        };
    };

    template <typename Derived>
    struct Stringifiable
    {
        std::ostream& stringify(std::ostream& stream, StringificationOptions options) const
        {
            options.in_object = true;
            options.ignore_name = false;
            AdaptedStringifier <Derived> stringifier;
            return stringifier(stream, *static_cast <Derived const*> (this), options);
        }
        template <typename Base>
        std::ostream& stringify(std::ostream& stream, StringificationOptions options) const
        {
            options.in_object = true;
            options.ignore_name = false;
            AdaptedStringifier <Derived, Base> stringifier;
            return stringifier(stream, *static_cast <Derived const*> (this), options);
        }
        virtual ~Stringifiable() = default;
    };
}

#endif // JSS_FUSION_ADAPTED_STRUCT_H_INCLUDED
