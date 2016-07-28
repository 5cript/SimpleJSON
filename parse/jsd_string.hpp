#pragma once

#include "jsd_core.hpp"

namespace JSON
{
	void parse(std::string& value, std::string const& name,
			   PropertyTree const& object, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS);
}
