#include "jsd_options.hpp"

namespace JSON
{
	ParsingOptions::ParsingOptions(InvalidPropertyHandlingBehaviour invalidPropertyHandler,
                                   InvalidPathHandlingBehaviour invalidPathHandler)
		: invalidPropertyHandler(invalidPropertyHandler)
		, invalidPathHandler(invalidPathHandler)
	{}
}
