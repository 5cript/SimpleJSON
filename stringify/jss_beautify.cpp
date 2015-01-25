#include "jss_beautify.h"

namespace JSON
{
    std::string js_beautify(std::string const& str, int pretab)
    {
        std::stringstream sstr;
        int tab = pretab;
        bool was_closed = false;
        for (auto const& i : str)
        {
            if (i == '{')
            {
                sstr << "\n";
                for (int j = 0; j != tab; ++j) sstr << '\t';
                sstr << "{\n";
                tab++;
                for (int j = 0; j != tab; ++j) sstr << '\t';
                was_closed = false;
            }
            else if (i == '}')
            {
                tab--;
                sstr << "\n";
                for (int j = 0; j != tab; ++j) sstr << '\t';
                sstr << "}\n";
                was_closed = true;
            }
            else if (i == ',')
            {
                if (was_closed)
                {
                    auto temp = sstr.str();
                    sstr.str({});
                    sstr.clear();
                    temp.pop_back();
                    sstr << temp;
                }
                sstr << ",\n";
                for (int j = 0; j != tab; ++j) sstr << '\t';
                was_closed = false;
            }
            else
            {
                sstr << i;
                was_closed = false;
            }
        }
        return sstr.str();
    }
}
