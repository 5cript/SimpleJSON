#ifndef JSD_STRING_H_INCLUDED
#define JSD_STRING_H_INCLUDED

#include "jsd_core.h"

namespace JSON
{
	void parse(std::string& value, std::string const& name,
			   PropertyTree const& object, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS);
}

#endif
