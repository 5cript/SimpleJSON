#include "xml_converter.h"
#include "../parse/jsd_generic_parser.h"

#include <boost/property_tree/xml_parser.hpp>

#include <iostream>

namespace JSON
{
    std::ostream& convertJsonToXml(std::ostream& ostream, std::istream& istream)
    {
        auto tree = parse_json(istream);

        boost::property_tree::write_xml(ostream, tree.tree);

        return ostream;
    }
}
