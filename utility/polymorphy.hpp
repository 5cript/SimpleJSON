#pragma once

#include "../parse/jsd_core.hpp"
#include "tmp_util/fundamental/pack.hpp"

#include <stdexcept>
#include <type_traits>
#include <functional>
#include <iostream>

#include <boost/preprocessor/seq/enum.hpp>
#include <boost/type_index.hpp>

#ifdef __BORLANDC__
#	include <boost/algorithm/string/replace.hpp>
#endif

/**
 *  WARNING! This does not work if you can construct a polymorphic type with the base class.
 *  This only works with abstract base classes or interfaces.
 *  This restriction is not made here explicitly (using static_assert), because you could still
 *  not instantiate the base by choice, even though it is not abstract.
 */

namespace JSON
{
    struct no_poly;

    template <typename T>
    struct polydecls
    {
        using type = no_poly;
    };

    template <typename T>
    struct is_polydecl
    {
        static constexpr bool const value = !std::is_same <typename polydecls <T>::type, no_poly>::value;
	};

	template <typename T>
	std::string type_name_factory()
	{
#if defined(JSON_TYPENAME_PATCH)
		return JSONPatch::type_name_factory <T>();
#elif defined(__BORLANDC__)
        auto name = boost::typeindex::type_id_with_cvr <T>().pretty_name();
		boost::replace_all(name, "@", "::");
        return name.substr(1, name.length() - 1);
#else
		return boost::typeindex::type_id_with_cvr <T>().pretty_name();
#endif
    }

    template <typename BaseT, typename PackT>
	struct dyn_cast_test {};

    template <typename BaseT, typename Head, typename... Tail>
    struct dyn_cast_test <BaseT, pack<Head, Tail...>>
    {
        static bool is_exact_type(BaseT const* poly_ptr)
        {
            return (dynamic_cast <Head const*> (poly_ptr) != nullptr);
        }
        static std::string find_type(BaseT const* poly_ptr)
        {
            if (!is_exact_type(poly_ptr))
                return dyn_cast_test <BaseT, pack<Tail...>>::find_type(poly_ptr);
            else
				return type_name_factory <Head>();
        }
        static BaseT* create(std::string const& type_name)
        {
			if (type_name_factory <Head>() == type_name)
            {
                return new Head;
            }
            else
                return dyn_cast_test <BaseT, pack<Tail...>>::create(type_name);
        }
        template <template <typename...> class T, typename... List> \
        static void smart_pointer_get(T<List...>& smart, std::string const& type_name, std::string const& name,\
                                      PropertyTree const& tree, ParsingOptions const& options)
		{
			if (type_name_factory <Head>() == type_name)
			{
                smart.reset(new Head);
                //static_cast <Head*> (smart.get())->Head::parse(name, tree, options);
                dynamic_cast <Head*> (smart.get())->Head::parse(name, tree, options);
            }
            else
                dyn_cast_test <BaseT, pack<Tail...>>::smart_pointer_get(smart, type_name, name, tree, options);
        }
        template <template <typename...> class T, typename... List>
        static void smart_pointer_set(T<List...> const& smart, std::ostream& stream, StringificationOptions const& options)
        {
            if (is_exact_type(smart.get()))
            {
                //static_cast <Head*> (smart.get())->template stringify <BaseT>(stream, options);
                dynamic_cast <Head*> (smart.get())->template stringify <BaseT>(stream, options);
            }
            else {
                dyn_cast_test <BaseT, pack<Tail...>>::smart_pointer_set(smart, stream, options);
            }
        }
    };

    template <typename BaseT>
    struct dyn_cast_test <BaseT, pack <>>
    {
        static std::string find_type(BaseT const*)
        {
            throw std::runtime_error("dynamic cast cannot find any subclass");
        }
        static BaseT* create(std::string const&)
        {
            throw std::runtime_error("subclass not found, could not instantiate type with given type");
        }
        template <template <typename...> class T, typename... List>
        static void smart_pointer_get(T<List...>&, std::string const&, std::string const&,
                                      PropertyTree const&, ParsingOptions const&)
        {
            throw std::runtime_error("subclass not found, could not reset smart pointer with given type");
        }
        template <template <typename...> class T, typename... List>
        static void smart_pointer_set(T<List...> const&, std::ostream&, StringificationOptions const&)
        {
            throw std::runtime_error("subclass not found, could not find stringify function");
        }
    };
}

#define JSON_DECLARE_POLYMORPHIC(interface, deriv_sequence) \
namespace JSON \
{ \
    template <> \
    struct polydecls <interface> \
    { \
        using type = pack <\
            BOOST_PP_SEQ_ENUM(deriv_sequence) \
        >; \
        \
        static std::string identify_type(interface const* poly_ptr) \
        { \
            return dyn_cast_test <interface, type>::find_type(poly_ptr); \
        } \
        \
        template <typename U> \
        static interface* create(std::string const& type_name) \
        { \
            return dyn_cast_test <interface, type>::create(type_name); \
        } \
        \
        template <template <typename...> class T, typename... List> \
        static void smart_pointer_get(T<List...>& smart, std::string const& type_name, std::string const& name,\
                                      PropertyTree const& tree, ParsingOptions const& options) \
        { \
            dyn_cast_test <interface, type>::smart_pointer_get(smart, type_name, name, tree, options); \
        } \
        \
        template <template <typename...> class T, typename... List> \
        static void smart_pointer_set(T<List...> const& smart, std::ostream& stream, StringificationOptions const& options) \
        { \
            dyn_cast_test <interface, type>::smart_pointer_set(smart, stream, options); \
        } \
    }; \
}
