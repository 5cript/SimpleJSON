#include "jsd_generic_parser.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <sstream>

namespace JSON
{
	using namespace boost::property_tree;

	PropertyTree::PropertyTree(boost::property_tree::ptree tree)
		: tree(tree)
	{

	}
// ======================================================================================================
	PropertyTree parse_json(std::istream& stream)
	{
		ptree pt;
		read_json(stream, pt);
		return PropertyTree(pt);
	}
	PropertyTree parse_json(std::string const& str)
	{
		std::stringstream sstr(str);

		ptree pt;
		read_json(sstr, pt);
		return PropertyTree(pt);
	}

	boost::optional<PropertyTree> parse_auto(std::istream& stream)
	{
		ptree pt;
		do {
			try {
				read_xml(stream, pt);
				break;
			}
			catch (...) {
				// failed
			}

			try {
				read_ini(stream, pt);
				break;
			}
			catch (...) {
				// failed
			}

			try {
				read_json(stream, pt);
				break;
			}
			catch (...) {
				// failed
			}

			return boost::optional<PropertyTree>();
		} while (0);

		return boost::make_optional( PropertyTree(pt) );
	}

	boost::optional<PropertyTree> parse_xml(std::istream& stream)
	{
		ptree pt;

		try {
			read_xml(stream, pt);
			return boost::make_optional( PropertyTree(pt) );
		}
		catch (...) {
			return boost::optional<PropertyTree>();
		}
	}
}
