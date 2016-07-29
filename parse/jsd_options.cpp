#include "jsd_options.hpp"

namespace JSON
{
	ParsingOptions::ParsingOptions(InvalidPropertyHandlingBehaviour invalidPropertyHandler,
                                   InvalidPathHandlingBehaviour invalidPathHandler,
                                   bool strings_are_binary)
		: invalidPropertyHandler(invalidPropertyHandler)
		, invalidPathHandler(invalidPathHandler)
		, strings_are_binary(strings_are_binary)
	{}
}
