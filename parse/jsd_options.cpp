#include "jsd_options.h"

namespace JSON
{
	ParsingOptions::ParsingOptions(InvalidPropertyHandlingBehaviour invalidPropertyHandler,
                                   InvalidPathHandlingBehaviour invalidPathHandler)
		: invalidPropertyHandler(invalidPropertyHandler)
		, invalidPathHandler(invalidPathHandler)
	{}
}
