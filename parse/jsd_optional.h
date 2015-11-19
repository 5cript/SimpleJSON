#ifndef JSD_OPTIONAL_H_INCLUDED
#define JSD_OPTIONAL_H_INCLUDED

#include <boost/optional.hpp>

namespace JSON
{
    template <typename T>
    void parse(boost::optional <T>& value, std::string const& name,
               PropertyTree const& object, ParsingOptions const& options = DEFAULT_PARSER_OPTIONS)
    {
        try
        {
            auto opt = object.tree.get_optional <T> (name);
            if (!opt)
                return; // its ok, it was optional
            else
                value = opt.get();
        }
        catch (boost::property_tree::ptree_bad_data& exc)
        {
			DEFAULT_PROPERTY_ERROR_HANDLER(T(), T());
        }
        // cannot throw ptree_bad_path
    }
}

#endif // JSD_OPTIONAL_H_INCLUDED
