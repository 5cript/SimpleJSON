# SimpleJSON


1. [Preface](https://github.com/5cript/SimpleJSON#preface)
2. [Introduction](https://github.com/5cript/SimpleJSON#introduction)
3. [Details](https://github.com/5cript/SimpleJSON#details)
  * [How does stringify work?](https://github.com/5cript/SimpleJSON#how-does-stringify-work)
  * [stringify behaviour (and STL stringification)](https://github.com/5cript/SimpleJSON#stringify-behaviour-and-stl-stuff-stringification)
4. [Reference](https://github.com/5cript/SimpleJSON#reference)

## Preface
Please submit pull requests if you don't agree with some behaviour or found a bug, I would appreciate it.
I recently changed the versioning on the releases to indicate that this lib ist still under development and free to change.
 
## Introduction
A JSON stringifier / parser that uses boost fusion introspection methods for automagic struct &lt;-> JSON conversion

Its supports almost all STL contstructs in stringify and the most important for parse. 
With the STL as a basis it is an easy to extend mechanism using classes. Use boost fusion and the provided utility
(see example below) or provide your own parse/stringify methods.

INFO: I changed the versions from 1.x something something to 0.x something something, because I realised that I am likely not going to hesitate breaking interface or implementation. This has still very much potential and is wide open for improvements.

NOTE: This library is not fine tuned for speed. 

Dependencies:
> boost/property_tree <br>
> boost/fusion <br>
> boost/mpl <br>
> boost/phoenix <br>

Code example:
```C++
#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include "SimpleJSON/parse/jsd.h"
#   include "SimpleJSON/parse/jsd_convenience.h"
#   include "SimpleJSON/stringify/jss.h"
#   include "SimpleJSON/tringify/jss_fusion_adapted_struct.h"
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

## Details
### How does stringify work?
There is just one function for stringification. This stringify function is heavily overloaded and makes use of SFINAE in almost every overload. The compiler then finds the correct overload to stringify the parameter.

* The library supports almost all STL containers (stringify supports even more) as well as fundamental types. <br>
* Containers will decay into json arrays, if their value_type is a stringifiable (this is recursive).
* Classes will turn into objects, if it is adapted, derives from FusionStruct<> and each parameter is stringifiable.
* The stringify class member is called if provided, you have to make sure yourself that what you produce makes sense.

### stringify behaviour (and STL stuff stringification)
It is quite import to know how certain STL constructs translate into JSON and here is a brief summary:

What it is  | What it becomes | Remarks
------------- | ------------- | -------------
std::vector  | [...] |
std::deque | [...] |
std::list | [...] |
std::forward_list | [...] | Who uses forward_list anyway?
std::array | [...] |
std::pair  | {"first": ..., "second": ...} |
std::atomic &lt;T> | What T would produce. | Caution! Obviously calls load().
std::bitset | [1, 0, ...] |
std::string | "..." |
fundamental types | themselves |
JSON::IteratorRange <STL_IteratorT> | [...] |
std::map &lt;T, U> | [[T1, U1], [T2, U2], ...] | General case
std::map &lt;std::string, T> | {"key": "value", "key2": "value2", ...} | Specialization
std::mutex | nothing | Only use if you must!
std::set | [...] |
std::stack | [...] | Don't use if possible, better use deque.
std::queue | [...] | Don't use if possible, better use deque.
std::shared_ptr &lt;T> | What T would produce. | Throws if invalid.
std::unique_ptr &lt;T> | What T would produce. | Throws if invalid.
std::weak_ptr &lt;T> | What T would produce | Throws if invalid.
std::tuple | {"_1": ..., "_2": ..., ...} | 
std::valarray &lt;T> | [...] | 
boost::optional <T> | T or nothing | Very useful for making things optional... ofc

## Reference
Please visit the wiki: [Wiki](https://github.com/5cript/SimpleJSON/wiki)
