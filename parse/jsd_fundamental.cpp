#ifndef JSD_FUNDAMENTAL_CPP_INCLUDED
#define JSD_FUNDAMENTAL_CPP_INCLUDED

#include "jsd_fundamental.hpp"

namespace JSON
{
    void parse(bool& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options)
    {
        try
        {
            SJSON_GET_VALUE(bool, name, value, bool());
        }
		catch (boost::property_tree::ptree_bad_data& exc)
		{
			SJSON_DEFAULT_PROPERTY_ERROR_HANDLER(char(), char());
		}
        catch (boost::property_tree::ptree_bad_path& exc)
        {
			SJSON_DEFAULT_PATH_ERROR_HANDLER(char(), char());
        }
    }
    void parse(char& value, std::string const& name,
              PropertyTree const& object, ParsingOptions const& options)
    {
        try
        {
            std::string s;
            SJSON_GET_VALUE(std::string, name, s, char());

            if (!s.empty())
                value = s[0];
        }
		catch (boost::property_tree::ptree_bad_data& exc)
		{
			SJSON_DEFAULT_PROPERTY_ERROR_HANDLER(char(), char());
		}
        catch (boost::property_tree::ptree_bad_path& exc)
        {
			SJSON_DEFAULT_PATH_ERROR_HANDLER(char(), char());
        }
    }
    void parse(wchar_t& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options)
    {
        try
        {
            std::string s;
            SJSON_GET_VALUE(std::string, name, s, wchar_t());

            if (!s.empty())
                value = s[0];
        }
		catch (boost::property_tree::ptree_bad_data& exc)
		{
			SJSON_DEFAULT_PROPERTY_ERROR_HANDLER(wchar_t(), wchar_t());
		}
        catch (boost::property_tree::ptree_bad_path& exc)
        {
			SJSON_DEFAULT_PATH_ERROR_HANDLER(wchar_t(), wchar_t());
        }
    }
}



#endif // JSD_FUNDAMENTAL_CPP_INCLUDED
