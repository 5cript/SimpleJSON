# SimpleJSON
A JSON stringifier / parser that uses boost fusion introspection methods for automagic struct &lt;-> JSON conversion

INFO: The library changed from version 1.0 to 1.1 so that it breaks working code.
      All functions now receive a stream parameter and return this passed stream.
      This is far more convenient and faster too. Its "the C++ style". Sorry for inconvenience, but
      this is certainly a step forward.

This library is not fine tuned for speed. 

Dependencies:
> boost/property_tree <br>
> boost/fusion <br>
> boost/mpl <br>
> boost/phoenix <br>

Code example:
```C++
#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include "parse/jsd.h"
#   include "parse/jsd_convenience.h"
#   include "stringify/jss.h"
#   include "stringify/jss_fusion_adapted_struct.h"
#endif

#include <string>
#include <vector>
#include <sstream>

struct ConfigContent : public JSON::FusionStruct <ConfigContent>
                     , public JSON::ParsableStruct <ConfigContent>
{
    int id;
    std::string libPath;
    std::vector <std::string> someContainer;
};

BOOST_FUSION_ADAPT_STRUCT
(
    ConfigContent,
    (int, id)
    (std::string, libPath)
    (std::vector <std::string>, someContainer)
)

ConfigContent parse(std::istream& json)
{
    ConfigContent cc;
    auto tree = JSON::parse_json(json);
    JSON::parse(cc, "config_content", tree);
    return cc;
}

std::ostream& stringify(std::ostream& stream, ConfigContent const& cc)
{
    stream << "{";
    JSON::try_stringify(stream, "config_content", cc, JSON::ProduceNamedOutput);
    stream << "}";
    return stream;
}

int main()
{
    ConfigContent cc;
    cc.id = 2;
    cc.libPath = "./somewhere";
    cc.someContainer = {"Hello", "World"};

    std::stringstream sstr;
    stringify(sstr, cc);
    auto unnecessarilyComplexCopy = parse(sstr);

    /////////////////////////////////////////////////////////////////////////
    // Lets check if we got what we set
    /////////////////////////////////////////////////////////////////////////

    std::cout << sstr.str() << "\n\n";
    std::cout << unnecessarilyComplexCopy.id << "\n";
    std::cout << unnecessarilyComplexCopy.libPath << "\n";
    for (auto const& i : unnecessarilyComplexCopy.someContainer)
        std::cout << i << "\n";
}
```
