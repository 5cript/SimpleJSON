#pragma once

#include "jsd_core.hpp"
#include "jsd_object.hpp"

#include <boost/fusion/mpl.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/phoenix/phoenix.hpp>
#include <boost/fusion/include/size.hpp>

#include <iostream>
#include <functional>
#include <type_traits>

namespace JSON
{
    template <typename T>
    class AdaptedParser
    {
    public:
        void operator()(T& object, std::string const& name, PropertyTree const& tree, ParsingOptions const& options) const
        {
            //! If you get an Error here, you likely forgot to use BOOST_FUSION_ADAPT_STRUCT !

            typedef boost::mpl::range_c<
                int,
                0,
                boost::fusion::result_of::size<T>::type::value
            > range;

            std::stringstream sstr;
            boost::mpl::for_each<range>(std::bind<void>
			(
				_helper(boost::fusion::result_of::size<T>::type::value),
				std::placeholders::_1,
				std::ref(object),
				std::ref(name),
				std::ref(tree),
				std::ref(options)
			));
        }
    private:
        class _helper
        {
        public:
            template<class Index>
            void operator()(Index, T& object, std::string const& name, PropertyTree const& tree, ParsingOptions const& options) const
            {
                if (name.empty())
                    parse(boost::fusion::at<Index>(object),
                          boost::fusion::extension::struct_member_name<T, Index::value>::call(),
                          tree, options);
                else
                    parse(boost::fusion::at<Index>(object),
                          name + "." + boost::fusion::extension::struct_member_name<T, Index::value>::call(),
                          tree, options);
            }
            _helper(int len) : len(len) {}
        private:
            int len;
        };
    };

    template <typename Derived>
    struct Parsable
    {
        void parse(std::string const& name, PropertyTree const& tree, ParsingOptions const& options = {})
        {
            AdaptedParser<Derived> parser;
            parser(*static_cast <Derived*> (this), name, tree, options);
        }
        virtual ~Parsable() = default;
    };
}
