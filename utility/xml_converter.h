#ifndef XML_CONVERTER_H_INCLUDED
#define XML_CONVERTER_H_INCLUDED

#include <iosfwd>

namespace JSON
{
    /**
     *  Converts the json istream contents to xml and writes it to the ostream.
     *  It is not defined, what happens when streams overlap.
     *
     *  @param ostream A stream to write to
     *  @param istream A stream to read from
     *
     *  @return The ostream passed as parameter;
     */
    std::ostream& convertJsonToXml(std::ostream& ostream, std::istream& istream);
}

#endif // XML_CONVERTER_H_INCLUDED
