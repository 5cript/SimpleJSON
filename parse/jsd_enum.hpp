#pragma once

#include "jsd_core.hpp"
#include "../utility/tmp_util/type_of_size.hpp"

#include <type_traits>

namespace JSON
{
    template <typename T>
	void parse(T& value, std::string const& name,
			   PropertyTree const& object, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS,
			   typename std::enable_if<std::is_enum<T>::value>::type* = nullptr)
    {
        try
		{
            using integer_type = typename type_of_size <sizeof(T) * 8>::type;
            integer_type temp;
		    GET_VALUE(integer_type, name, temp, T());
		    value = static_cast <T>(temp);
		}
		catch (boost::property_tree::ptree_bad_data& exc)
		{
			DEFAULT_PROPERTY_ERROR_HANDLER(T(), T());
		}
        catch (boost::property_tree::ptree_bad_path& exc)
        {
			DEFAULT_PATH_ERROR_HANDLER(T(), T());
        }
    }
}
