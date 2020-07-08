#pragma once

/**
 *  Used if a class has a nested json thing that cannot be well built by data structures.
 *  Its trusted to contain valid JSON.
 */

namespace JSON
{
    struct json_string
    {
        std::string json;

        json_string()
            : json{}
        {
        }

        json_string(std::string json)
            : json{std::move(json)}
        {
        }

        json_string(char const* json)
            : json{json}
        {
        }

        json_string& operator=(json_string&&) = default;
        json_string& operator=(json_string const&) = default;
        json_string(json_string const&) = default;
        json_string(json_string&&) = default;

        json_string& operator=(char const* cstr)
        {
            json = cstr;
            return *this;
        }
        json_string& operator=(std::string const& str)
        {
            json = str;
            return *this;
        }
    };

    inline std::ostream& operator<<(std::ostream& stream, json_string const& jstring)
    {
        stream << jstring.json;
        return stream;
    }
}

