#ifndef JSD_FUNDAMENTAL_H_INCLUDED
#define JSD_FUNDAMENTAL_H_INCLUDED

#include "jsd_core.h"

namespace JSON
{
	template <typename T,
			  class = typename std::enable_if<   std::is_arithmetic<T>::value
                                              || std::is_enum<T>::value         >::type 
			 >
	void js_parse(T& value, std::string const& name,
					  PropertyTree const& object, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS)
	{
		try
		{
			value = object.tree.get<T>(name);
		}
		catch (boost::property_tree::ptree_bad_data& exc)
		{
			DEFAULT_ERROR_HANDLER(T(), T());
		}
	}
}

#endif