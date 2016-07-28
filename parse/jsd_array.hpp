#ifndef JSD_ARRAY_H_INCLUDED
#define JSD_ARRAY_H_INCLUDED

#include "jsd_core.hpp"
#include <array>
#include <stdexcept>

namespace JSON
{
	template <typename T, std::size_t N>
	void parse(std::array<T, N>& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS)
	{
		try
		{
		    GET_CHILD(name, pt, {});

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

#endif
