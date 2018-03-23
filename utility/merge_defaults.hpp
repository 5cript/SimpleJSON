#pragma once

#include "../parse/jsd_object.hpp"
#include "../parse/jsd_generic_parser.hpp"
#include "../utility/rename.hpp"

#include "optional_info.hpp"
#include "tmp_util/type_of_size.hpp"

#include <boost/optional.hpp>

#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/fusion/include/size.hpp>

#include <utility>
#include <type_traits>
#include <unordered_map>

namespace JSON
{
    /**
     *  Fill loaded json data with defaults and return whether anything was added or not.
     */
    template <typename T>
    typename std::enable_if <Internal::isParsable<T>::value, bool>::type
    merge_defaults(
        T& value,
        std::string const& name,
        PropertyTree const& object,
        /* optional */ PropertyTree* difference = nullptr,
        ParsingOptions const& options = {}
    );

    template <typename T>
    class JsonComparator
    {
    public:
        JsonComparator(PropertyTree* difference)
            : difference_{difference}
            , anyDefaults_{false}
        {}

        bool operator()(std::string const& name, PropertyTree const& tree, T& defaults, ParsingOptions const& options)
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
				std::ref(*this),
				std::cref(name),
				std::cref(tree),
                std::ref(defaults),
                std::cref(options)
			));

			return anyDefaults_;
        }

    private:
        class _helper
        {
        public:
            template<class Index>
            void operator()(
                Index,
                JsonComparator& owner,
                std::string const& name,
                PropertyTree const& tree,
                T& defaults,
                ParsingOptions const& options
            ) const
            {
                auto& member = boost::fusion::at<Index>(defaults);
                using type = typename boost::fusion::result_of::at_c<T, Index::value>::type;

                std::string deeperName;
                if (name.empty())
                    deeperName = boost::fusion::extension::struct_member_name<T, Index::value>::call();
                else
                    deeperName = name + "." + boost::fusion::extension::struct_member_name<T, Index::value>::call();

                owner.merge <type>(deeperName, tree, member, options);
            }
            _helper(int len) : len(len) {}
        private:
            int len;
        };

        template <typename U>
        void merge(std::string const& name, PropertyTree const& tree, U& defaults, ParsingOptions const& options)
        {
            anyDefaults_ |= merge_defaults(defaults, name, tree, difference_, options);
        }

        PropertyTree* difference_;
        bool anyDefaults_;
    };

    template <typename T>
    typename std::enable_if <Internal::isParsable<T>::value, bool>::type
    merge_defaults(
        T& value,
        std::string const& name,
        PropertyTree const& object,
        /* optional */ PropertyTree* difference,
        ParsingOptions const& options
    )
    {
        JsonComparator <typename std::decay<T>::type> checker{difference};
        return checker(name, object, value, options);
    }

    #define SJSON_MERGE_DEFAULTS_HAS_R(X) \
        auto opt = object.tree.get_child_optional(name); \
        if (opt)

    #define SJSON_MERGE_DEFAULTS_HAS(X) \
        auto opt = object.tree.get_optional <std::decay_t <decltype(value)>>(name); \
        if (opt)

    #define SJSON_MERGE_DEFAULTS_DOES_NOT_HAVE \
        else \
        { \
            if (difference) \
                difference->tree.put(name, name); \
            return true; \
        }

    template <typename T, template <typename, class = std::allocator <T> > class ContainerT>
    bool merge_defaults(
        ContainerT<T>& value,
        std::string const& name,
        PropertyTree const& object,
        PropertyTree* difference,
        ParsingOptions const& options
    )
    {
        SJSON_MERGE_DEFAULTS_HAS_R(name)
        {
            bool anyDefaults = false;
            value.clear();
            for (auto const& i : opt.get())
            {
                T temp;
                anyDefaults |= merge_defaults(temp, {}, i.second, difference, options);
                value.emplace_back(std::move(temp));
            }
            return anyDefaults;
        }
        SJSON_MERGE_DEFAULTS_DOES_NOT_HAVE
    }

    template <
        typename T,
		class = typename std::enable_if<(
            std::is_arithmetic<T>::value &&
            !std::is_same<T, char>::value &&
            !std::is_same<T, wchar_t>::value) &&
            !std::is_enum<T>::value
        >::type
    >
    bool merge_defaults(
        T& value,
        std::string const& name,
        PropertyTree const& object,
        PropertyTree* difference,
        ParsingOptions const& options
    )
    {
        SJSON_MERGE_DEFAULTS_HAS(name)
        {
            value = opt.get();
            return false;
        }
        SJSON_MERGE_DEFAULTS_DOES_NOT_HAVE
    }

    bool merge_defaults(
        std::string& value,
        std::string const& name,
        PropertyTree const& object,
        PropertyTree* difference,
        ParsingOptions const& options
    );

    template <typename T>
    bool merge_defaults(
        boost::optional <T>& value,
        std::string const& name,
        PropertyTree const& object,
        PropertyTree* difference,
        ParsingOptions const& options
    )
    {
        if (object.tree.get_optional <std::string> (name))
        {
            T v;
            bool anyDefaults = merge_defaults(v, name, object, difference, options);
            value = v;
            return anyDefaults;
        }
        else
            return false;
    }

    template <typename T>
    typename std::enable_if<std::is_enum<T>::value, bool>::type
	merge_defaults(
        T& value,
        std::string const& name,
        PropertyTree const& object,
        PropertyTree* difference,
        ParsingOptions const& options
    )
    {
        using integer_type = typename type_of_size <sizeof(T) * 8>::type;
        auto opt = object.tree.get_optional <integer_type> (name);
        if (opt)
            value = static_cast <T>(opt.get());
        SJSON_MERGE_DEFAULTS_DOES_NOT_HAVE

        return false;
    }

    template <typename ValueT, typename CompareT = std::less <ValueT>, class AllocT = std::allocator <ValueT>>
	bool merge_defaults(
        std::map<std::string, ValueT, CompareT, AllocT>& value,
        std::string const& name,
        PropertyTree const& object,
        PropertyTree* difference,
        ParsingOptions const& options = {}
    )
    {
        SJSON_MERGE_DEFAULTS_HAS_R(name)
        {
            bool anyDefaults = false;
            for (auto const& i : opt.get())
            {
                ValueT temp;
                anyDefaults |= merge_defaults(temp, {}, i.second, difference, options);
                value[i.first] = temp;
            }
            return anyDefaults;
        }
        SJSON_MERGE_DEFAULTS_DOES_NOT_HAVE
    }

    template <typename T, std::size_t N>
    bool merge_defaults(
        std::array<T, N>& value,
        std::string const& name,
        PropertyTree const& object,
        PropertyTree* difference,
        ParsingOptions const& options = {}
    )
    {
        using namespace std::string_literals;

        SJSON_MERGE_DEFAULTS_HAS_R(name)
        {
            int pos = 0;
            bool anyDefaults = false;
            auto const& result = opt.get();
            for (auto const& i : result)
            {
                T temp;
                anyDefaults |= merge_defaults(temp, {}, i.second, difference, options);
                if (pos != N)
                    value[pos++] = temp;
                else
                    throw std::out_of_range(("there is more data to be read, but the array is full: "s + name).c_str());
            }
            for (; pos < static_cast <decltype(pos)>(N); ++pos)
                value[pos] = 0;
            return anyDefaults;
        }
        SJSON_MERGE_DEFAULTS_DOES_NOT_HAVE
    }

    template <typename T, typename U>
    bool merge_defaults(
        std::pair <T, U>& value,
        std::string const& name,
        PropertyTree const& object,
        PropertyTree* difference,
        ParsingOptions const& options = {}
    )
    {
        return
            merge_defaults(value.first, name+".first", object, difference, options) &&
            merge_defaults(value.second, name+".second", object, difference, options)
		;
    }

    template <typename T, typename Name>
    bool merge_defaults(
        rename <T, Name>& value,
        std::string const& name,
        PropertyTree const& object,
        PropertyTree* difference,
        ParsingOptions const& options = {}
    )
    {
        std::string relName;
        auto pos = name.find_last_of(".");
        if (pos == std::string::npos)
            relName = Name::c_str;
        else
            relName = name.substr(0, pos + 1) + Name::c_str;

        return merge_defaults(value.getValue(), relName, object, difference, options);
    }

    template <typename T>
    bool merge_defaults(
        std::set<T>& value,
        std::string const& name,
        PropertyTree const& object,
        PropertyTree* difference,
        ParsingOptions const& options = {}
    )
    {
        SJSON_MERGE_DEFAULTS_HAS_R(name)
        {
            auto const& result = opt.get();
            bool anyDefaults = false;
            for (auto const& i : result)
            {
                T temp;
                anyDefaults |= merge_defaults(temp, "", i.second, difference, options);
                value.insert(std::move(temp));
            }
            return anyDefaults;
        }
        SJSON_MERGE_DEFAULTS_DOES_NOT_HAVE
    }

    template <
        typename ValueT,
        typename HashT = std::hash <std::string>,
        typename PredT = std::equal_to <std::string>,
        typename AllocT = std::allocator <std::pair <std::string const, ValueT>>
    >
    bool merge_defaults(
        std::unordered_map<std::string, ValueT, HashT, PredT, AllocT>& value,
        std::string const& name,
        PropertyTree const& object,
        PropertyTree* difference,
        ParsingOptions const& options = {}
    )
    {
        SJSON_MERGE_DEFAULTS_HAS_R(name)
        {
            auto const& result = opt.get();
            bool anyDefaults = false;
            for (auto const& i : result)
            {
                ValueT temp;
                anyDefaults |= merge_defaults(temp, {}, i.second, difference, options);
                value[i.first] = temp;
            }
            return anyDefaults;
        }
        SJSON_MERGE_DEFAULTS_DOES_NOT_HAVE
    }
}
