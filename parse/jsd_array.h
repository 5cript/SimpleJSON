#ifndef JSD_ARRAY_H_INCLUDED
#define JSD_ARRAY_H_INCLUDED

#include "jsd_core.h"
#include <array>
#include <stdexcept>

namespace JSON
{
	template <typename T, unsigned N>
	void js_parse(std::array<T, N>& value, std::string const& name,
					  PropertyTree const& object, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS)
	{
		try
		{
			auto pt = object.tree.get_child(name);
			int pos = 0;
			for (auto const& i : pt)
			{
				T temp;
				js_parse(temp, "", i.second, options);
				if (pos != N)
					value[pos++] = temp;
				else if (options.invBehaviour != InvalidPropertyHandlingBehaviour::IGNORE)
					throw std::out_of_range("there is more data to be read, but the array is full");
			}
		}
		catch (boost::property_tree::ptree_bad_data& exc)
		{
			DEFAULT_ERROR_HANDLER({}, {});
		}
	}
}

#endif