#pragma once

#include "../parse/jsd_object.hpp"
#include "../utility/optional_info.hpp"

#include <type_traits>
#include <boost/optional.hpp>

#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/fusion/include/size.hpp>

namespace JSON
{
    template <typename T>
    void fill_missing(std::string const& name, PropertyTree& tree);

    template <typename T>
    class Filler
    {
public:
        template <typename U = T>
        typename std::enable_if <Internal::isParsable<U>::value, void>::type
        operator()(std::string const& name, PropertyTree& tree) const
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
				std::ref(name),
				std::ref(tree)
			));
        }

        template <typename U = T>
        typename std::enable_if <!Internal::isParsable<U>::value, void>::type
        operator()(std::string const& name, PropertyTree& tree) const
        {
            //std::cout << "endpoint: " << name << "\n";
            default_initialize <U>(name, tree);
        }

    private:
        class _helper
        {
        public:
            template<class Index>
            void operator()(Index, std::string const& name, PropertyTree& tree) const
            {
                using type = typename boost::fusion::result_of::at_c<T, Index::value>::type;

                if (!name.empty())
                    default_initialize <type>(name, tree);

                std::string deeperName;
                if (name.empty())
                    deeperName = boost::fusion::extension::struct_member_name<T, Index::value>::call();
                else
                    deeperName = name + "." + boost::fusion::extension::struct_member_name<T, Index::value>::call();

                std::cout << deeperName << "\n";
                fill_missing <type>(deeperName, tree);
            }
            _helper(int len) : len(len) {}
        private:
            int len;
        };

        template <typename U>
        typename std::enable_if <!Internal::is_optional <U>::value, void>::type
        static default_initialize(std::string const& name, PropertyTree& tree)
        {
            //using raw = typename std::decay<U>::type;
            auto opt = tree.tree.get_optional <std::string>(name);
            if (!opt)
                tree.tree.put(name, std::string{});
        }

        template <typename U>
        typename std::enable_if <Internal::is_optional <U>::value, void>::type
        static default_initialize(std::string const& name, PropertyTree& tree)
        {
            // do nothing
        }
    };

    template <typename T>
    void fill_missing(std::string const& name, PropertyTree& tree)
    {
        Filler <typename std::decay<T>::type> filler;
        filler(name, tree);
    }
}
