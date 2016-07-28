#pragma once

#include "jsd_core.hpp"

namespace JSON
{
	template <typename T, typename U>
	void parse(std::pair <T, U>& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS)
	{
		try
		{
		    GET_VALUE(T, name+".first", value.first, std::make_pair(T(), U()));
		    GET_VALUE(T, name+".second", value.second, std::make_pair(T(), U()));
		}
		catch (boost::property_tree::ptree_bad_data& exc)
		{
			DEFAULT_PROPERTY_ERROR_HANDLER(std::make_pair(T(), U()), std::make_pair(T(), U()));
		}
        catch (boost::property_tree::ptree_bad_path& exc)
        {
			DEFAULT_PATH_ERROR_HANDLER(std::make_pair(T(), U()), std::make_pair(T(), U()));
        }

	}
}
