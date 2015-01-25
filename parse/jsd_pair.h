#ifndef JSD_PAIR_H_INCLUDED
#define JSD_PAIR_H_INCLUDED

#include "jsd_core.h"

namespace JSON
{
	template <typename T, typename U>
	void js_parse(std::pair <T, U>& value, std::string const& name,
					  PropertyTree const& object, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS)
	{
		try
		{
			value.first = object.tree.get<T>(name+".first");
			value.second = object.tree.get<U>(name+".second");
		}
		catch (boost::property_tree::ptree_bad_data& exc)
		{
			DEFAULT_ERROR_HANDLER(std::make_pair(T(), U()), std::make_pair(T(), U()));
		}
	}
}

#endif