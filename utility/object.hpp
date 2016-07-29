#pragma once

#include "../stringify/jss_core.hpp"
#include "../parse/jsd_core.hpp"

namespace JSON
{
    class ObjectBuilder
    {
    public:
        ObjectBuilder();

        template <typename T>
        void add(std::string const& key, T&& value)
        {
            comma();

            stringify(result_, key, std::forward <T&&> (value), JSON::ProduceNamedOutput);
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
    };

    class ObjectReader
    {
    public:
        ObjectReader(PropertyTree const* tree, std::string const& path = "");

        template <typename T>
        void get(std::string const& name, T& object)
        {
            std::string path;
            if (!name_.empty())
                path += name_ + ".";
            parse(object, path + name, *tree_);
        }

        template <typename T>
        T get(std::string const& name)
        {
            T result;
            get(name, result);
            return result;
        }

    private:
        PropertyTree const* tree_;
        std::string name_;
    };
}
