#ifndef JSD_FUSION_ADAPTED_STRUCT_H_INCLUDED
#define JSD_FUSION_ADAPTED_STRUCT_H_INCLUDED

#include "jsd_core.h"

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
    struct ParsableStruct
    {
        void parse(std::string const& name, PropertyTree const& tree, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS)
        {
            AdaptedParser<Derived> parser;
            parser(*static_cast <Derived*> (this), name, tree, options);
        }
        virtual ~ParsableStruct() = default;
    };

	namespace Internal {
		template <typename Type, typename enable = void>
		class isParsableStruct
		{
		public:
			static const bool value = false;
		};

		template <typename Type>
		class isParsableStruct <Type, typename std::enable_if<std::is_class<Type>::value>::type>
		{
		private:
			class yes { char m; };
			class no { yes m[2];};
			struct BaseMixin
			{
				void parse(std::string const&,
							  PropertyTree const&,
							  ParsingOptions const&)
				{}
			};
			struct Base : public Type, public BaseMixin {};
			template <typename T, T t>  class Helper{};

			template <typename U>
			static no deduce(U*, Helper<
				void (BaseMixin::*)(std::string const&,
									PropertyTree const&,
									ParsingOptions const&),
				&U::parse>* = nullptr);
			static yes deduce(...);
		public:
			static const bool value = sizeof(yes) == sizeof(deduce((Base*)(0)));
		};
	}

	template <typename T>
	typename std::enable_if <Internal::isParsableStruct<T>::value, void>::type
	parse(T& value, std::string const& name, PropertyTree const& tree, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS)
	{
		value.parse(name, tree, options);
	}
}

#endif // JSS_FUSION_ADAPTED_STRUCT_H_INCLUDED
