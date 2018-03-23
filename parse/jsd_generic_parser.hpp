#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/optional.hpp>

#include <string>
#include <vector>
#include <memory>
#include <set>
#include <map>

namespace JSON
{
	struct PropertyTree
	{
		boost::property_tree::ptree tree;

		PropertyTree(boost::property_tree::ptree tree = {});
		void to_stream(std::ostream& stream);
	};

	PropertyTree parse_json(std::istream& stream);
	PropertyTree parse_json(std::string const& str);
	boost::optional<PropertyTree> parse_auto(std::istream& stream);
	boost::optional<PropertyTree> parse_xml(std::istream& stream);
}
