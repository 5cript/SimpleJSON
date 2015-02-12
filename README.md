# SimpleJSON
A JSON stringifier / parser that uses boost fusion introspection methods for automagic POD struct &lt;-> JSON conversion

This library is not fine tuned for speed. 
The slowest part should be the boost/property_tree library used for parsing JSON.

Dependencies:
> boost/property_tree <br>
> boost/fusion

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

struct ConfigContent : public JSON::FusionStruct <ConfigContent>
                     , public JSON::ParsableStruct <ConfigContent>
{
  int id;
  std::string libPath;
  std::vector <std::string> someArray;
}

BOOST_FUSION_ADAPT_STRUCT
(
    ConfigContent,
    (int, id)
    (std::string, libPath)
    (std::vector <std::string>, someArray)
)

ConfigContent parse(std::string const& json)
{
  ConfigContent cc;
  auto tree = JSON::parse_json(json);
  JSON::js_parse(cc, "config_content", tree);
}

std::string stringify(ConfigContent const& cc)
{
  return JSON::js_try_stringify("config_content", cc);
}

int main() 
{
  std::string str;
  ConfigContent cc;
  
  str = stringify(cc);
  auto unnecessarilyComplexCopy = parse(str);
  
  // unnecessarilyComplexCopy == cc
}
```
