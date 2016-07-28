#ifndef JSD_UNORDERED_MAP_H_INCLUDED
#define JSD_UNORDERED_MAP_H_INCLUDED

#include "jsd_core.hpp"
#include <unordered_map>

namespace JSON
{
	template <typename ValueT, typename HashT = std::hash <std::string>, class PredT = std::equal_to <std::string>,
              typename AllocT = std::allocator <std::pair <const std::string, ValueT>>>
	void parse(std::unordered_map<std::string, ValueT, HashT, PredT, AllocT>& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS)
	{
		try
		{
			GET_CHILD(name, pt, (std::unordered_map<std::string, ValueT>()));
			for (auto const& i : pt)
			{
				ValueT temp;
				parse(temp, "", i.second, options);
				value[i.first] = temp;
			}
		}
		catch (boost::property_tree::ptree_bad_data& exc)
		{
			DEFAULT_PROPERTY_ERROR_HANDLER((std::unordered_map<std::string, ValueT>()), (std::unordered_map<std::string, ValueT>()));
		}
        catch (boost::property_tree::ptree_bad_path& exc)
        {
			DEFAULT_PATH_ERROR_HANDLER((std::unordered_map<std::string, ValueT>()), (std::unordered_map<std::string, ValueT>()));
        }
	}
}

#endif // JSD_UNORDERED_MAP_H_INCLUDED
