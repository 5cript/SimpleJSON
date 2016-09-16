#pragma once

#include "jsd_generic_parser.hpp"
#include "jsd_options.hpp"

#include <type_traits>
#include <utility>

namespace JSON
{
    /*
    template <typename T, bool Selector>
    struct ResetIfAssignableImpl
    {
        static void constexpr exec(...) {}
    };

    template <typename T>
    struct ResetIfAssignableImpl <T, true>
    {
        static void constexpr exec(T& t)
        {
            t = {};
        }
    };

    template <typename T>
    struct ResetIfAssignable
    {
        static void constexpr exec(T& t)
        {
            ResetIfAssignableImpl <T, std::is_copy_assignable <T>::value>::exec(t);
        }
    };

    template <typename T, bool Selector>
    struct AssignIfAssignableImpl
    {
        static void constexpr exec(...) {}
    };

    template <typename T>
    struct AssignIfAssignableImpl <T, true>
    {
        template <typename V>
        static void constexpr exec(T& t, V&& value)
        {
            t = std::forward <V&&> (value);
        }
    };

    template <typename T>
    struct AssignIfAssignable
    {
        template <typename V>
        static void constexpr exec(T& t, V&& value)
        {
            AssignIfAssignableImpl <T, std::is_trivially_copy_assignable <T>::value && std::is_copy_constructible <T>::value>::exec(t, value);
        }
    };
    */

    #define GET_VALUE(TYPE, NAME, TEMP, TAG_VALUE) \
    if (options.invalidPathHandler == InvalidPathHandlingBehaviour::IGNORE_ALL_ERROR || \
        options.invalidPathHandler == InvalidPathHandlingBehaviour::TAG) \
    { \
        /* ResetIfAssignable <typename std::decay <decltype(value)>::type>::exec(value);  */\
        auto opt = object.tree.get_optional <TYPE> (NAME); \
        if (!opt) { \
            if (options.invalidPathHandler == InvalidPathHandlingBehaviour::IGNORE_ALL_ERROR) \
                return; \
            else { \
                /* AssignIfAssignable <typename std::decay <decltype(value)>::type>::exec(value, typename std::decay <decltype(value)>::type {TAG_VALUE}); */ \
                return; \
            } \
        } \
        TEMP = opt.get(); \
    } \
    else \
    { \
        TEMP = object.tree.get <TYPE> (NAME); \
    }
    // MAKRO END

    #define GET_CHILD(NAME, RESULT, TAG_VALUE) \
    decltype(object.tree) RESULT;\
    if (options.invalidPathHandler == InvalidPathHandlingBehaviour::IGNORE_ALL_ERROR || \
        options.invalidPathHandler == InvalidPathHandlingBehaviour::TAG) \
    { \
        /* ResetIfAssignable <typename std::decay <decltype(value)>::type>::exec(value); */ \
        auto opt = object.tree.get_child_optional (NAME); \
        if (!opt) { \
            if (options.invalidPathHandler == InvalidPathHandlingBehaviour::IGNORE_ALL_ERROR) \
                return; \
            else { \
                /* AssignIfAssignable <typename std::decay <decltype(value)>::type>::exec(value, typename std::decay <decltype(value)>::type {TAG_VALUE}); */ \
                return; \
            } \
        } \
        RESULT = opt.get(); \
    } \
    else \
    { \
        RESULT = object.tree.get_child (NAME); \
    }
    // MAKRO END

    #define DEFAULT_PROPERTY_ERROR_HANDLER(DEFAULT_VALUE, TAG_VALUE)		\
	switch (options.invalidPropertyHandler) {								\
		case (InvalidPropertyHandlingBehaviour::DEFAULT):		\
			/* value = {}; */\
			return;												\
		case (InvalidPropertyHandlingBehaviour::TAG):			\
			\
			return;												\
		case (InvalidPropertyHandlingBehaviour::IGNORE_ALL_ERROR):		\
			return;												\
		case (InvalidPropertyHandlingBehaviour::THROW):			\
			throw exc;											\
	}
	// MAKRO END

	#define DEFAULT_PATH_ERROR_HANDLER(DEFAULT_VALUE, TAG_VALUE)		\
	switch (options.invalidPathHandler) {								\
		case (InvalidPathHandlingBehaviour::DEFAULT):		\
			/* value = {}; */\
			return;												\
		case (InvalidPathHandlingBehaviour::TAG):			\
			\
			return;												\
		case (InvalidPathHandlingBehaviour::IGNORE_ALL_ERROR):		\
			return;												\
		case (InvalidPathHandlingBehaviour::THROW):			\
			throw exc;											\
	}
	// MAKRO END

	inline std::string member_name(std::string const& base_name, std::string const& name)
	{
	    if (base_name.empty())
            return "";
        else
            return base_name + "." + name;
	}
}
