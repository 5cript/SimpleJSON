#ifndef JSD_CORE_H_INCLUDED
#define JSD_CORE_H_INCLUDED

#include "jsd_generic_parser.h"
#include "jsd_options.h"

#include <type_traits>
#include <utility>

namespace JSON
{
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
		default:												\
			return;												\
	}															\
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
		default:												\
			return;												\
	}															\
	// MAKRO END
}

#endif
