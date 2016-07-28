#pragma once

#include "jsd_generic_parser.hpp"
#include "jsd_options.hpp"

#include <type_traits>
#include <utility>

namespace JSON
{
    #define GET_VALUE(TYPE, NAME, TEMP, TAG_VALUE) \
    if (options.invalidPathHandler == InvalidPathHandlingBehaviour::IGNORE_ALL_ERROR || \
        options.invalidPathHandler == InvalidPathHandlingBehaviour::TAG) \
    { \
        value = {}; \
        auto opt = object.tree.get_optional <TYPE> (NAME); \
        if (!opt) { \
            if (options.invalidPathHandler == InvalidPathHandlingBehaviour::IGNORE_ALL_ERROR) \
                return; \
            else { \
                value = TAG_VALUE; \
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
        value = {}; \
        auto opt = object.tree.get_child_optional (NAME); \
        if (!opt) { \
            if (options.invalidPathHandler == InvalidPathHandlingBehaviour::IGNORE_ALL_ERROR) \
                return; \
            else { \
                value = TAG_VALUE; \
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
			value = DEFAULT_VALUE;								\
			return;												\
		case (InvalidPropertyHandlingBehaviour::TAG):			\
			value = TAG_VALUE;									\
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
			value = DEFAULT_VALUE;								\
			return;												\
		case (InvalidPathHandlingBehaviour::TAG):			\
			value = TAG_VALUE;									\
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
