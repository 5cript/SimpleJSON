#pragma once

#include <boost/optional.hpp>

#include "../stringify/jss_core.hpp"
#include "../parse/jsd_core.hpp"

namespace JSON
{
    class ObjectBuilder
    {
    public:
        ObjectBuilder(JSON::StringificationOptions options = {});

        void setOptions(JSON::StringificationOptions options);
        JSON::StringificationOptions& getOptions();

        template <typename T>
		ObjectBuilder& add(std::string const& key, T&& value)
		{
			comma();

			stringify(result_, key, std::forward <T&&> (value), options_);
			return *this;
		}

		template <typename T>
		ObjectBuilder& addRaw(std::string const& key, std::string const& value)
		{
			comma();

			result_ << '"' << key << "\":";
            result_ << value;

			return *this;
		}

        std::string get() const
        {
            return result_.str() + "}";
        }

    private:
        void comma();

    private:
        std::stringstream result_;
        bool fresh_;
        JSON::StringificationOptions options_;
    };

    class ObjectReader
    {
    public:
        ObjectReader(PropertyTree const* tree, std::string const& path = "", JSON::ParsingOptions options = {});
        ObjectReader(PropertyTree const* tree, JSON::ParsingOptions options);
        ObjectReader(boost::property_tree::ptree::iterator iter, std::string const& path = "", JSON::ParsingOptions options = {});

        void setOptions(JSON::ParsingOptions options);
        JSON::ParsingOptions& getOptions();

        template <typename T>
		ObjectReader const& get(std::string const& name, T& object) const
		{
			std::string path;
			if (!name_.empty())
				path += name_ + ".";

			if (tree_ != nullptr)
				parse(object, path + name, *tree_, options_);
			else
				parse(object, path + name, treeCopy_.get(), options_);

			return *this;
        }

        template <typename T>
        T get(std::string const& name) const
        {
            T result;
            get(name, result);
            return result;
        }

    private:
        PropertyTree const* tree_;
        boost::optional <PropertyTree> treeCopy_;
        std::string name_;
        JSON::ParsingOptions options_;
    };
}
