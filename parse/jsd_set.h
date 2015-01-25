#ifndef JSD_SET_H_INCLUDED
#define JSD_SET_H_INCLUDED

#include "jsd_core.h"
#include "jsd_container.h"

#include <set>

namespace JSON
{
	template <typename T>
	void js_parse(std::set<T>& value, std::string const& name,
					  PropertyTree const& object, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS)
	{
		try
		{
			auto pt = object.tree.get_child(name);
			for (auto const& i : pt)
			{
				T temp;
				js_parse(temp, "", i.second, options);
				value.insert(std::move(temp));
			}
		}
		catch (boost::property_tree::ptree_bad_path& exc)
		{
			DEFAULT_ERROR_HANDLER(std::set<T>{}, std::set<T>{});
		}
	}
}

#endif