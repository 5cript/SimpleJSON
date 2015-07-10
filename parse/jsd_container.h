#ifndef JSD_CONTAINER_H_INCLUDED
#define JSD_CONTAINER_H_INCLUDED

#include "jsd_core.h"

namespace JSON
{
	template <typename T, template <typename, class = std::allocator <T> > class ContainerT>
	void parse(ContainerT<T>& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS)
	{
		try
		{
			auto pt = object.tree.get_child(name);
			for (auto const& i : pt)
			{
				T temp;
				parse(temp, "", i.second, options);
				value.emplace_back(std::move(temp));
			}
		}
		catch (boost::property_tree::ptree_bad_path& exc)
		{
			DEFAULT_ERROR_HANDLER({}, {});
		}
	}
}

#endif
