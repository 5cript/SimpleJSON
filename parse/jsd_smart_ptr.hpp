#pragma once

#include "../utility/polymorphy.hpp"
#include "../utility/property_tree_probe.hpp"

#include <type_traits>

namespace JSON
{
    namespace internal
    {
        template <typename T, bool ClassType, bool Poly>
        struct smart_pointer_parser
        {
        };

        template <typename T>
        struct smart_pointer_parser <T, true, false>
        {
            static void get(T& value, std::string const& name, PropertyTree const& object, ParsingOptions const& options)
            {
                value.reset(new typename std::decay<T>::type::element_type{});
                value->parse(name, object, options);
            }
        };

        template <typename T>
        struct smart_pointer_parser <T, false, false>
        {
            static void get(T& value, std::string const& name, PropertyTree const& object, ParsingOptions const& options)
            {
                using element_type = typename std::decay<T>::type::element_type;
                value.reset(new element_type{});
                GET_VALUE(element_type, name, *value, {});
            }
        };

        template <typename T>
        struct smart_pointer_parser <T, true, true>
        {
            static void get(T& value, std::string const& name, PropertyTree const& object, ParsingOptions const& options)
            {
                using polydecl_type = polydecls <typename T::element_type>;

                try
                {
                    // causes exceptions for proper error.
                    object.tree.get <tree_probe> (name);

                    // expects type name
                    auto type_name = object.tree.get_optional <std::string> (name + ".__cxx_type");
                    if (!type_name)
                        throw std::runtime_error (
                            std::string("object with name '") +
                            name +
                            "' and base type '" +
                            boost::typeindex::type_id_with_cvr<typename T::element_type>().pretty_name() +
                            "' is declared polymorphic, but does not come with a type definition __cxx_type"
                        );

                    // read smart pointer contents.
                    polydecl_type::smart_pointer_get(value, type_name.get(), name, object, options);
                }
                catch (boost::property_tree::ptree_bad_data& exc)
                {
                    DEFAULT_PROPERTY_ERROR_HANDLER(T(), T());
                }
                catch (boost::property_tree::ptree_bad_path& exc)
                {
                    DEFAULT_PATH_ERROR_HANDLER(T(), T());
                }
            }
        };

        template <typename T>
        struct smart_pointer_parser <T, false, true>
        {
            static void get(T& value, std::string const& name, PropertyTree const& object, ParsingOptions const& options)
            {
                // static_assert(false, "Not a class but polymorphic? you did something wrong!");
                // poly, but not a class
            }
        };

        template <typename T>
        void parse_smart_ptr(T& value, std::string const& name,
                   PropertyTree const& object, ParsingOptions const& options = {})
        {

            using element_type = typename std::decay<decltype(value)>::type::element_type;

            internal::smart_pointer_parser <T,
                                            std::is_class <element_type>::value,
                                            is_polydecl <element_type>::value>::get(value,
                                                                                    name,
                                                                                    object,
                                                                                    options);
        }
    }
}
