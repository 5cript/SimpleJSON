#pragma once

#include "jsd_core.hpp"
#include <map>

namespace JSON
{
	template <typename ValueT, typename CompareT = std::less <ValueT>, class AllocT = std::allocator <ValueT>>
	void parse(std::map<std::string, ValueT, CompareT, AllocT>& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS)
	{
		try
		{
			GET_CHILD(name, pt, (std::map<std::string, ValueT, CompareT, AllocT>()));
			for (auto const& i : pt)
			{
				ValueT temp;
				parse(temp, "", i.second, options);
				value[i.first] = temp;
			}
		}
		catch (boost::property_tree::ptree_bad_data& exc)
		{
			DEFAULT_PROPERTY_ERROR_HANDLER((std::map<std::string, ValueT, CompareT, AllocT>()), (std::map<std::string, ValueT, CompareT, AllocT>()));
		}
        catch (boost::property_tree::ptree_bad_path& exc)
        {
			DEFAULT_PATH_ERROR_HANDLER((std::map<std::string, ValueT, CompareT, AllocT>()), (std::map<std::string, ValueT, CompareT, AllocT>()));
        }
	}
}
