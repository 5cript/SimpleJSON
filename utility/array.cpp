#include "array.hpp"

namespace JSON
{
//#####################################################################################################################
    ArrayBuilder::ArrayBuilder(JSON::StringificationOptions options)
        : result_{}
        , fresh_{}
        , options_{std::move(options)}
    {
        result_ << '[';
    }
//---------------------------------------------------------------------------------------------------------------------
    void ArrayBuilder::comma()
    {
        if (!fresh_)
        {
            result_ << ",";
        }
        else
            fresh_ = false;
    }
//---------------------------------------------------------------------------------------------------------------------
    void ArrayBuilder::setOptions(JSON::StringificationOptions options)
    {
        options_ = options;
    }
//---------------------------------------------------------------------------------------------------------------------
    JSON::StringificationOptions& ArrayBuilder::getOptions()
    {
        return options_;
    }
//#####################################################################################################################
    ArrayReader::ArrayReader(PropertyTree const& tree, std::string const& path, JSON::ParsingOptions options)
        : name_{path}
        , options_{std::move(options)}
    {
        tree_.tree = tree.tree.get_child (path);
        reset();
    }
//---------------------------------------------------------------------------------------------------------------------
    ArrayReader::ArrayReader(PropertyTree const& tree, JSON::ParsingOptions options)
        : name_{}
        , options_{std::move(options)}
    {
        tree_.tree = tree.tree.get_child ("");
        reset();
    }
//---------------------------------------------------------------------------------------------------------------------
    ArrayReader::operator bool() const
    {
        return iter_ != tree_.tree.end();
    }
//---------------------------------------------------------------------------------------------------------------------
    void ArrayReader::reset()
    {
        iter_ = tree_.tree.begin();
    }
//---------------------------------------------------------------------------------------------------------------------
    void ArrayReader::setOptions(JSON::ParsingOptions options)
    {
        options_ = options;
    }
//---------------------------------------------------------------------------------------------------------------------
    JSON::ParsingOptions& ArrayReader::getOptions()
    {
        return options_;
    }
//#####################################################################################################################
}
