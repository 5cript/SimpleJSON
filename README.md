# SimpleJSON


1. [Preface](https://github.com/5cript/SimpleJSON#preface)
2. [Introduction](https://github.com/5cript/SimpleJSON#introduction)
3. [Details](https://github.com/5cript/SimpleJSON#details)
  * [How does stringify work?](https://github.com/5cript/SimpleJSON#how-does-stringify-work)
  * [stringify behaviour (and STL stringification)](https://github.com/5cript/SimpleJSON#stringify-behaviour-and-stl-stuff-stringification)
4. [Reference](https://github.com/5cript/SimpleJSON#reference)

## Preface
Please submit pull requests if you don't agree with some behaviour or found a bug, I would appreciate it.
The library is further matured now and changes less. 

This library can parse and stringify and is designed for easy use.
Nobody wants to write parsing and stringification methods for every class they write. We rather want it
to work "just like that" without thinking about it. This is where this library fits in.
This idea of producing and consuming JSON has become the "Hello World of Introspection".

Since release 0.3, the library also features basic JSON beautification using boost iostreams.
 
## Introduction
A JSON stringifier / parser that uses boost fusion introspection methods for automagic struct &lt;-> JSON conversion

Its supports almost all STL contstructs in stringify and the most important for parse. 
With the STL as a basis it is an easy to extend mechanism using classes. Use boost fusion and the provided utility
(see example below) or provide your own parse/stringify methods.

NOTE: The performance of this library is mostly influenced by boost property tree which is used for parsing JSON.
The main focus of this library is not speed, but ease of use and convenience. If you want to be fast, try RapidJson (not saying it is particullarly slow, but probably not suitable for high data frequency or big bulk data application)

Dependencies:
> boost/property_tree <br>
> boost/fusion <br>
> boost/mpl <br>

Code example:
```C++
#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include "SimpleJSON/parse/jsd.h"
#   include "SimpleJSON/parse/jsd_convenience.h"
#   include "SimpleJSON/stringify/jss.h"
#   include "SimpleJSON/stringify/jss_fusion_adapted_struct.h"
#endif

#include <string>
#include <vector>
#include <sstream>

struct ConfigContent : public JSON::Stringifiable <ConfigContent>
                     , public JSON::Parsable <ConfigContent>
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
* Classes will turn into objects, if it is adapted, derives from Stringifiable<> and each member is stringifiable.
* For other classes, the "stringify" method is called, if provided, but then you will have to make sure on your own to produce a valid output. (The base64 wrapper uses this).

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
std::map &lt;std::string, T> | {"key": "value", "key2": "value2", ...} | A map basically represents a JSON object
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
