#pragma once

#include "../stringify/jss_core.hpp"
#include "../parse/jsd_core.hpp"

namespace JSON
{
    class ArrayBuilder
    {
    public:
        ArrayBuilder(JSON::StringificationOptions options = {});

		template <typename T>
		ArrayBuilder& add(T&& value)
		{
			comma();

			stringify(result_, "", std::forward <T&&> (value), options_);

			return *this;
		}

		ArrayBuilder& addRaw(std::string const& value)
		{
			comma();

			result_ << value;

			return *this;
        }

        std::string get() const
        {
            return result_.str() + "]";
        }

        /**
         *  Sets the options.
         */
        void setOptions(JSON::StringificationOptions options);
        JSON::StringificationOptions& getOptions();

    private:
        void comma();

    private:
        std::stringstream result_;
        bool fresh_;
        JSON::StringificationOptions options_;
    };

    class ArrayReader
    {
    public:
        ArrayReader(PropertyTree const& tree, std::string const& path = "", JSON::ParsingOptions options = {});
        ArrayReader(PropertyTree const& tree, JSON::ParsingOptions options);

        /**
         *  Retrieve the next array element.
         *
         *  @return Returns whether there are more elements or not.
         */
        template <typename T>
        bool getNext(T& object)
        {
            if (!operator bool())
                return false;

            parse(object, "", iter_->second, options_);

            ++iter_;

            return operator bool();
        }

        /**
         *  Returns the next element as an iterator.
         */
        boost::property_tree::ptree::iterator getNext()
        {
            auto iterCpy = iter_;
            iter_++;
            return iterCpy;
        }

        /**
         *  Checks whether there are more elements to read.
         *
         *  @return iterator < end_iterator.
         */
        explicit operator bool() const;

        /**
         *  Reset the iterator back to the beginning.
         */
        void reset();

        /**
         *  Sets the options.
         */
        void setOptions(JSON::ParsingOptions options);
        JSON::ParsingOptions& getOptions();

    private:
        PropertyTree tree_;
        boost::property_tree::ptree::iterator iter_;
        std::string name_;
        JSON::ParsingOptions options_;
    };
}
