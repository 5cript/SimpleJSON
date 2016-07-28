#pragma once

#include <iosfwd>
#include <stack>
#include <ctype.h>                        // toupper
#include <boost/iostreams/categories.hpp> // output_filter_tag
#include <boost/iostreams/operations.hpp> // put


/**
 *  This class is not meant to be used anywhere else than inside a try_stringify() call.
 *  It is used to produce very simple beautified json output.
 **/

namespace JSON
{
    enum class NestingState
    {
        IN_ARRAY,
        IN_CLASS
    };

    class BeautifiedStreamWrapper
    {
    public:
        typedef char                   char_type;
        typedef boost::iostreams::output_filter_tag  category;

        BeautifiedStreamWrapper();

        template <typename Sink>
        bool put(Sink& snk, char c)
        {
            namespace io = boost::iostreams;

            escape_ = false;
            if (disabled_)
                if (c == '\\')
                    escape_ = true;

            if (c == '"' && !escape_)
                disabled_ = !disabled_;

            if (disabled_)
            {
                io::put(snk, c);
                return true;
            }

            if (c == '{')
            {
                if (nestingStack_.top() == NestingState::IN_ARRAY)
                {
                    io::put(snk, '\n');
                    for (int i = 0; i != indentation_; ++i)
                        io::put(snk, '\t');
                }

                nestingStack_.push(NestingState::IN_CLASS);
            }
            else if (c == '[')
                nestingStack_.push(NestingState::IN_ARRAY);
            else if (c == '}' || c == ']') // assuming that json data is well formed
                nestingStack_.pop();

            if (c == '}' && indentation_ > 0)
                indentation_--;

            if (c == '{')
                indentation_++;

            if (c == '}')
            {
                io::put(snk, '\n');
                for (int i = 0; i != indentation_; ++i)
                    io::put(snk, '\t');
            }

            io::put(snk, c);

            if (c == ':')
                io::put(snk, ' ');

            if (c == '{' || (c == ',' && nestingStack_.top() != NestingState::IN_ARRAY))
            {
                io::put(snk, '\n');
                for (int i = 0; i != indentation_; ++i)
                    io::put(snk, '\t');
            }
            else if (c == ',' && nestingStack_.top() == NestingState::IN_ARRAY)
            {
                io::put(snk, ' ');
            }

            return true;
        }

    private:
        int indentation_;
        bool escape_;
        bool disabled_;
        std::stack <NestingState> nestingStack_;
    };
}
