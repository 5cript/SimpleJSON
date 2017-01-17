#include "object.hpp"

namespace JSON
{
//#####################################################################################################################
    ObjectBuilder::ObjectBuilder(JSON::StringificationOptions options)
        : result_{}
        , fresh_{true}
        , options_{std::move(options)}
    {
        result_ << "{";
        options_.in_object = true;
    }
//---------------------------------------------------------------------------------------------------------------------
    void ObjectBuilder::comma()
    {
        if (!fresh_)
			result_ << ",";
        else
            fresh_ = false;
    }
//---------------------------------------------------------------------------------------------------------------------
    void ObjectBuilder::setOptions(JSON::StringificationOptions options)
    {
        options_ = options;
    }
//---------------------------------------------------------------------------------------------------------------------
    JSON::StringificationOptions& ObjectBuilder::getOptions()
    {
        return options_;
    }
//#####################################################################################################################
    ObjectReader::ObjectReader(PropertyTree const* tree, std::string const& path, JSON::ParsingOptions options)
        : tree_{tree}
        , treeCopy_{boost::none}
        , name_{path}
        , options_{std::move(options)}
    {

    }
//---------------------------------------------------------------------------------------------------------------------
    ObjectReader::ObjectReader(PropertyTree const* tree, JSON::ParsingOptions options)
        : tree_{tree}
        , treeCopy_{boost::none}
        , name_{}
        , options_{std::move(options)}
    {
    }
//---------------------------------------------------------------------------------------------------------------------
    ObjectReader::ObjectReader(boost::property_tree::ptree::iterator iter, std::string const& path, JSON::ParsingOptions options)
        : tree_{nullptr}
        , treeCopy_{iter->second}
        , name_{path}
        , options_{std::move(options)}
    {
    }
//---------------------------------------------------------------------------------------------------------------------
    void ObjectReader::setOptions(JSON::ParsingOptions options)
    {
        options_ = options;
    }
//---------------------------------------------------------------------------------------------------------------------
    JSON::ParsingOptions& ObjectReader::getOptions()
    {
        return options_;
    }
//#####################################################################################################################
}
