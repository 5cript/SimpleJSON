#ifndef JSD_ATOMIC_H_INCLUDED
#define JSD_ATOMIC_H_INCLUDED

#include "jsd_core.h"
#include <atomic>

namespace JSON
{
	template <typename T>
	void parse(std::atomic<T>& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS)
	{
		try
		{
			T temp;
			parse(temp, name, object, options);
			value.store(std::move(temp));
		}
		catch (boost::property_tree::ptree_bad_data& exc)
		{
			DEFAULT_ERROR_HANDLER(T(), T());
		}
	}
}

#endif
