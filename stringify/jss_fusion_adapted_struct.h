#ifndef JSS_FUSION_ADAPTED_STRUCT_H_INCLUDED
#define JSS_FUSION_ADAPTED_STRUCT_H_INCLUDED

#include "jss_core.h"

#ifndef JSS_OBJECT_H_INCLUDED
#include "jss_object.h"
#endif

#include <iostream>
#include <boost/fusion/mpl.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>
//#include <boost/phoenix/phoenix.hpp>
#include <boost/fusion/include/size.hpp>

namespace JSON
{
    template <typename T>
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

            stream << '{';
            boost::mpl::for_each<range> (std::bind<void>(_helper(boost::fusion::result_of::size<T>::type::value), std::placeholders::_1, std::ref(stream), std::ref(object), std::ref(options)));
            stream << '}';
            return stream;
        }
    private:
        class _helper
        {
        public:
            template<class Index>
            void operator()(Index, std::ostream& os, T const& object, StringificationOptions const& options) const
            {
                stringify(os, boost::fusion::extension::struct_member_name<T, Index::value>::call(), boost::fusion::at<Index>(object), options);
                if (Index::value+1 != len)
                    os << options.delimiter;
            }
            _helper(int len) : len(len) {}
        private:
            int len;
        };
    };

    template <typename Derived>
    struct FusionStruct
    {
        std::ostream& stringify(std::ostream& stream, StringificationOptions options) const
        {
            options.in_object = true;
            options.ignore_name = false;
            AdaptedStringifier<Derived> stringifier;
            return stringifier(stream, *static_cast <Derived const*> (this), options);
        }
        virtual ~FusionStruct() = default;
    };
}

#endif // JSS_FUSION_ADAPTED_STRUCT_H_INCLUDED
