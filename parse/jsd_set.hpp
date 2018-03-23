#pragma once

#include "jsd_core.hpp"
#include "jsd_container.hpp"

#include <set>

namespace JSON
{
	template <typename T>
	void parse(std::set<T>& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options = {})
	{
		try
		{
			SJSON_GET_CHILD(name, pt, std::set<T>{});
			for (auto const& i : pt)
			{
				T temp;
				parse(temp, "", i.second, options);
				value.insert(std::move(temp));
			}
		}
		catch (boost::property_tree::ptree_bad_data& exc)
		{
			SJSON_DEFAULT_PROPERTY_ERROR_HANDLER(std::set<T>{}, std::set<T>{});
		}
        catch (boost::property_tree::ptree_bad_path& exc)
        {
			SJSON_DEFAULT_PATH_ERROR_HANDLER(std::set<T>{}, std::set<T>{});
        }
	}
}
