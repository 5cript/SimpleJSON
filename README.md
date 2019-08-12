# SimpleJSON ![Travis CI](https://travis-ci.org/5cript/SimpleJSON.svg?branch=master)


1. [Preface](https://github.com/5cript/SimpleJSON#preface) 
2. [Introduction](https://github.com/5cript/SimpleJSON#introduction)
3. [Example 1](https://github.com/5cript/SimpleJSON#Example1)
4. [Example 2](https://github.com/5cript/SimpleJSON#Example2)
4. [Useful Utility](https://github.com/5cript/SimpleJSON#Useful-Utility)
5. [Details](https://github.com/5cript/SimpleJSON#details)
  * [How does stringify work?](https://github.com/5cript/SimpleJSON#how-does-stringify-work)
  * [stringify behaviour (and STL stringification)](https://github.com/5cript/SimpleJSON#stringify-behaviour-and-stl-stuff-stringification)
6. [Reference](https://github.com/5cript/SimpleJSON#reference)

## Preface
Please submit pull requests if you don't agree with some behavior or found a bug, I would appreciate it.
The library is further matured now and changes less. 

This library can parse and stringify and is designed for ease of use.
Nobody wants to write parsing and stringification methods for every class they write. We rather want it
to work "just like that" without thinking about it. This is where this library fits in.
This idea of producing and consuming JSON has become the "Hello World of Introspection".

Since release 0.3, the library also features basic JSON beautification using boost iostreams.
 
## Introduction
A JSON stringifier / parser that uses boost fusion introspection methods for automagic struct &lt;-> JSON conversion

It supports almost all STL contstructs in stringify and the most important for parse. 
With the STL as a basis it is an easy to extend mechanism using classes. Use boost fusion and the provided utility
(see example below) or provide your own parse/stringify methods.

NOTE: The performance of this library is mostly influenced by boost property tree which is used for parsing JSON.
The main focus of this library is not speed, but ease of use and convenience. If you want to be fast, try RapidJson (not saying it is particularly slow, but probably not suitable for high data frequency or big bulk data application)

Dependencies:
> boost/property_tree <br>
> boost/fusion <br>
> boost/mpl <br>

## Example 0
```C++
#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include <SimpleJSON/parse/jsd.hpp>
#   include <SimpleJSON/stringify/jss.hpp>
#   include <SimpleJSON/stringify/jss_fusion_adapted_struct.hpp>
#endif

struct Object : public JSON::Stringifiable <Object>
              , public JSON::Parsable <Object>
{
    int A;
    std::string B;
    float C;
}; 
BOOST_FUSION_ADAPT_STRUCT(Object, A, B, C)

int main()
{
	auto o = JSON::make_from_json <Object> (R"(  
		{
			"A": 0,
			"B": "Hello",
			"C": 2.4
		}
	)");
}
```

## Example 1
```C++
#include <string>
#include <vector>
#include <sstream>

struct ConfigContent
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

SJSON_INJECT_STRINGIFY(ConfigContent)
SJSON_INJECT_PARSE(ConfigContent)

int main()
{
    ConfigContent cc;
    cc.id = 2;
    cc.libPath = "./somewhere";
    cc.someContainer = {"Hello", "World"};

    std::stringstream sstr;
    JSON::stringify(sstr, "", cc);
    ConfigContent unnecessarilyComplexCopy;
    JSON::parse(unnecessarilyComplexCopy, "", JSON::parse_json(sstr));

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

## Example 1B
An alternatvie to deriving. Does not handle polymorphic structs.
Especially useful for structs, you did not create.
```C++
struct ConfigContent
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

SJSON_INJECT_STRINGIFY(ConfigContent)
SJSON_INJECT_PARSE(ConfigContent)
```

## Example 2
 (Showing polymorphic serlialization / deserialization)
```C++
#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include <SimpleJSON/parse/jsd.hpp>
#   include <SimpleJSON/parse/jsd_convenience.hpp>
#   include <SimpleJSON/stringify/jss.hpp>
#   include <SimpleJSON/stringify/jss_fusion_adapted_struct.hpp>
#endif

#include "SimpleJSON/utility/polymorphy.hpp"

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

struct Base
{
    virtual ~Base() = default;
};

struct Line : Base
            , public JSON::Stringifiable <Line>
            , public JSON::Parsable <Line>
{
    std::string text;
};

struct PrimalList : Base
                  , public JSON::Stringifiable <PrimalList>
                  , public JSON::Parsable <PrimalList>
{
    std::vector <std::shared_ptr <Base>> elements;
};

JSON_DECLARE_POLYMORPHIC
(
    Base, (Line)(PrimalList)
)

BOOST_FUSION_ADAPT_STRUCT
(
    Base
)

BOOST_FUSION_ADAPT_STRUCT
(
    Line,
    text
)

BOOST_FUSION_ADAPT_STRUCT
(
    PrimalList,
    elements
)

template <typename T>
void parse(T& cc, std::istream& json)
{
    auto tree = JSON::parse_json(json);
    JSON::parse(cc, "json_pno", tree);
}

template <typename T>
std::ostream& stringify(std::ostream& stream, T const& cc)
{
    stream << "{";
    JSON::stringify(stream, "json_pno", cc, JSON::ProduceNamedOutput);
    stream << "}";
    return stream;
}

template <typename T>
//using smart_ptr_t = std::shared_ptr <T>;
using smart_ptr_t = std::unique_ptr<T>;

int main()
{
    smart_ptr_t <Base> a {new Line};
    static_cast <Line*> (a.get())->text = "test";

    std::stringstream sstr;
    stringify(sstr, a);

    smart_ptr_t <Base> b;
    parse(b, sstr);

    if (b)
        std::cout << "b!\n";

    //std::cout << JSON::polydecls <Base>::identify_type(b.get()) << "\n";

    /////////////////////////////////////////////////////////////////////////
    // Lets check if we got what we set
    /////////////////////////////////////////////////////////////////////////

    std::cout << static_cast <Line*> (b.get())->text << "\n";
}
```

## Example 3
Shows formatted output to a file
```C++
#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include <SimpleJSON/parse/jsd.hpp>
#   include <SimpleJSON/stringify/jss.hpp>
#   include <SimpleJSON/stringify/jss_fusion_adapted_struct.hpp>
#endif

struct Object : public JSON::Stringifiable <Object>
              , public JSON::Parsable <Object>
{
    int A;
    std::string B;
    float C;
}; 
BOOST_FUSION_ADAPT_STRUCT(Object, A, B, C)

int main()
{
    Object o;
    try_stringifiy_beautiful("myfile.json", "root", o);

    // alternative:
    {
        boost::iostreams::filtering_ostream filter;

        // or however else, refer to boost::iostreams doc
        filter.push(JSON::BeautifiedStreamWrapper{});
        filter.push(boost::iostreams::file_sink(file));

        // will not compile with a readable message, 
        // if Object is not a JSON::Stringifiable
        JSON::try_stringify_start(filter, "root", o);
    }
}
```

## Useful Utility
### JSON::Base64 < T> mem;
mem will be handled as a base64 string. useful if mem can contain any character or binary sequence, including quotes.

### JSON::fill_missing
```C++
auto tree = JSON::parse_json(str); // str contains some JSON.
JSON::fill_missing <MyJsonType> ("", tree); // missing members in the tree of MyJsonType get default constructed.
```
### JSON::rename <T, Name>
Renames a member. This is necessary if something is not a valid C++ identifier, such as "." or "6".
```C++
struct MyJsonType : /* ... */
{
	/**
	 *	SJSON_SHORT_STRING -> handles up to 16 characters. (prefer whenever possible)
	 *	SJSON_STRING -> handles up to 64 characters.
	 *	SJSON_LONG_STRING -> 256 chars. (dont use if possible, heavy compiler performance hit)
	 *	SJSON_LONG_LONG_STRING -> 1024 chars. (dont use if possible, heavy compiler performance hit)
	 */
	JSON::rename <std::string, SJSON_SHORT_STRING("__.bla")> blaProperty;
};
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
std::mutex | nothing | ??? why would you???
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
