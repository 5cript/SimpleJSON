#pragma once

#include "jsd_core.h"
#include "../utility/polymorphy.h"

#include <type_traits>
#include <memory>

namespace JSON
{
    namespace internal
    {
        template <typename T, bool ClassType, bool Enabler>
        struct type_dependent_retriever
        {
        };

        template <typename T>
        struct type_dependent_retriever <T, true, true>
        {
            static void get(T& value, std::string const& name, PropertyTree const& object, ParsingOptions const& options)
            {
                value.reset(new T{});
                value->parse(name, object, options);
            }
        };

        template <typename T>
        struct type_dependent_retriever <T, false, true>
        {
            static void get(T& value, std::string const& name, PropertyTree const& object, ParsingOptions const& options)
            {
                value.reset(new T{});
                GET_VALUE(T, name, *value, {});
            }
        };

        template <typename T>
        struct type_dependent_retriever <T, true, false>
        {
            static void get(T& value, std::string const& name, PropertyTree const& object, ParsingOptions const& options)
            {
                using polydecl_type = polydecls <typename T::element_type>;

                auto type_name = object.tree.get_optional <std::string> (name + ".__cxx_type");
                if (!type_name)
                    throw std::runtime_error ("object is declared polymorphic, but does not come with a type definition __cxx_type");
                polydecl_type::smart_pointer_get(value, type_name.get(), name, object, options);
            }
        };

        template <typename T>
        struct type_dependent_retriever <T, false, false>
        {
            static void get(T& value, std::string const& name, PropertyTree const& object, ParsingOptions const& options)
            {
                // static_assert(false, "Not a class but polymorphic? you did something wrong!");
                // poly, but not a class
            }
        };
    }

    template <typename T, typename Deleter>
    void parse(std::unique_ptr <T, Deleter>& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options = {})
    {
        using polydecl_type = polydecls <T>;

        internal::type_dependent_retriever <typename std::decay<decltype(value)>::type,
                                            std::is_class <T>::value,
                                            std::is_same <typename polydecl_type::type, no_poly>::value>::get(value,
                                                                                                              name,
                                                                                                              object,
                                                                                                              options);
    }
}
