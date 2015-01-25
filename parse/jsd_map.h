#ifndef JSD_MAP_H_INCLUDED
#define JSD_MAP_H_INCLUDED

#include "jsd_core.h"

namespace JSON
{
	template <typename ValueT, typename CompareT = std::less <ValueT>, class AllocT = std::allocator <ValueT>>
	void js_parse(std::map<std::string, ValueT, CompareT, AllocT>& value, std::string const& name,
					  PropertyTree const& object, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS)
	{
		try
		{
			auto pt = object.tree.get_child(name);
			for (auto const& i : pt)
			{
				ValueT temp;
				js_parse(temp, "", i.second, options);
				value[i.first] = temp;
			}
		}
		catch (boost::property_tree::ptree_bad_path& exc)
		{
			DEFAULT_ERROR_HANDLER((std::map<std::string, ValueT>()), (std::map<std::string, ValueT>()));
		}
	}
}

#endif