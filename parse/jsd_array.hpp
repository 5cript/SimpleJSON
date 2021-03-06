#pragma once

#include "jsd_core.hpp"
#include <array>
#include <stdexcept>

namespace JSON
{
	template <typename T, std::size_t N>
	void parse(std::array<T, N>& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options = {})
	{
		try
		{
		    SJSON_GET_CHILD(name, pt, {});

			int pos = 0;
			for (auto const& i : pt)
			{
				T temp;
				parse(temp, "", i.second, options);
				if (pos != N)
					value[pos++] = temp;
				else if (options.invalidPropertyHandler != InvalidPropertyHandlingBehaviour::IGNORE_ALL_ERROR)
					throw std::out_of_range("there is more data to be read, but the array is full");
			}
            for (; pos < static_cast <decltype(pos)>(N); ++pos)
                value[pos] = 0;
		}
		catch (boost::property_tree::ptree_bad_data& exc)
		{
			SJSON_DEFAULT_PROPERTY_ERROR_HANDLER({}, {});
		}
        catch (boost::property_tree::ptree_bad_path& exc)
        {
			SJSON_DEFAULT_PATH_ERROR_HANDLER({}, {});
        }
	}
}
