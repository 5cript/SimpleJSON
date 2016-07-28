#pragma once

#include "jsd_core.hpp"

namespace JSON
{
	template <typename T, template <typename, class = std::allocator <T> > class ContainerT>
	void parse(ContainerT<T>& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS)
	{
		try
		{
			GET_CHILD(name, pt, {});
			for (auto const& i : pt)
			{
				T temp;
				parse(temp, "", i.second, options);
				value.emplace_back(std::move(temp));
			}
		}
		catch (boost::property_tree::ptree_bad_data& exc)
		{
			DEFAULT_PROPERTY_ERROR_HANDLER({}, {});
		}
        catch (boost::property_tree::ptree_bad_path& exc)
        {
			DEFAULT_PATH_ERROR_HANDLER({}, {});
        }
	}
}
