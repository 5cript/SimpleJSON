#ifndef JSD_CORE_H_INCLUDED
#define JSD_CORE_H_INCLUDED

#include "jsd_generic_parser.h"
#include "jsd_options.h"

#include <type_traits>
#include <utility>

namespace JSON
{
	#define DEFAULT_ERROR_HANDLER(DEFAULT_VALUE, TAG_VALUE)		\
	switch (options.invBehaviour) {								\
		case (InvalidPropertyHandlingBehaviour::DEFAULT):		\
			value = DEFAULT_VALUE;								\
			return;												\
		case (InvalidPropertyHandlingBehaviour::TAG):			\
			value = TAG_VALUE;									\
			return;												\
		case (InvalidPropertyHandlingBehaviour::IGNORE):		\
			return;												\
		case (InvalidPropertyHandlingBehaviour::THROW):			\
			throw exc;											\
		default:												\
			return;												\
	}															\
	// MAKRO END
}

#endif