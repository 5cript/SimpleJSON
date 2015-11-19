#include "test.h"

#include <sstream>

#ifndef Q_MOC_RUN
#   include "parse/jsd.h"
#   include "parse/jsd_convenience.h"
#   include "stringify/jss.h"
#   include "stringify/jss_fusion_adapted_struct.h"
#endif

// TODO: needs more tests

// this does not need to be more complex. works recursively, so other tests will fulfill our needs
struct Object : public JSON::FusionStruct <Object>
              , public JSON::ParsableStruct <Object>
{
    int id = 5;
    std::string str = "Hello";
};

BOOST_FUSION_ADAPT_STRUCT
(
    Object,
    (int, id)
    (std::string, str)
)

#define TEST(O, RESULT_STRING) \
{ \
    std::stringstream sstr; \
    JSON::stringify (sstr, std::string("name"), O, JSON::DEFAULT_OPTIONS); \
    if (sstr.str() != RESULT_STRING) { std::cerr << "[FAIL   ] Expected: '" << RESULT_STRING << "' Got: '" << sstr.str() <<  "'\n"; failed++; }\
    else std::cout << "[SUCCESS] " << RESULT_STRING << "\n"; \
}

void testAll()
{
    int failed = 0;

    TEST(5, "5")
    TEST('c', "\"c\"")
    TEST(std::string{"Hello"}, "\"Hello\"")
    TEST((std::vector <char> {'a', 'b'}), "[\"a\",\"b\"]")
    TEST((std::pair <int, float>{3, 2.5f}), "{\"first\":3,\"second\":2.5}")
    TEST((std::bitset <3>{5u}), "[1,0,1]")
    TEST((std::forward_list <double> {2.3, 1.4, 0.5}), "[2.3,1.4,0.5]")
    TEST((std::map<std::string, int>{std::make_pair(std::string("hello"), 4), std::make_pair(std::string("world"), 8)}), "{\"hello\":4,\"world\":8}")
    TEST((std::multimap<int, int>{std::make_pair(2, 3), std::make_pair(4, 5)}), "[[2,3],[4,5]]")

    // NullptrException
    // TEST((nullptr), "")

    TEST((std::queue <int>{}), "[]")
    TEST((std::set <std::string> {"first", "second"}), "[\"first\",\"second\"]")
    TEST((std::tuple <int, float> {2, 1.2f}), "\"name\":{\"_0\":2,\"_1\":1.2}")

    TEST(Object{}, "{\"id\":5,\"str\":\"Hello\"}")
}
