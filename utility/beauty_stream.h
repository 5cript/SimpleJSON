#ifndef BEAUTY_STREAM_H_INCLUDED
#define BEAUTY_STREAM_H_INCLUDED

#include <iostream>

template <typename UnderlyingStreamT>
class BeautifiedStreamWrapper
{
public:
    using char_type = typename UnderlyingStreamT::char_type;
    using traits_type = typename UnderlyingStreamT::traits_type;
    using int_type = typename UnderlyingStreamT::int_type;
    using pos_type = typename UnderlyingStreamT::pos_type;
    using off_type = typename UnderlyingStreamT::off_type;

public:
    BeautifiedStreamWrapper(UnderlyingStreamT* stream)
        : stream_(stream)
    { }

    friend BeautifiedStreamWrapper& operator<<(BeautifiedStreamWrapper& stream, char_type c) {
        if (c == '}')
            indentation_--;

        for (ind = indentation_; ind; --ind)
            *stream_ << '\t';

        *stream_ << c;
        if (c == ',' || c == '{')
            *stream_ << '\n';
        if (c == '{')
            indentation_++;

        return *this;
    }

    friend BeautifiedStreamWrapper& operator<<(BeautifiedStreamWrapper& stream, std::basic_string <char_type> const& str) {
        if (str.back() == '}')
            indentation_--;

        for (ind = indentation_; ind; --ind)
            *stream_ << '\t';

        *stream_ << str;

        if (str.front() == ',' || str.front() == '{')
            *stream_ << '\n';
        if (str.front() == '{')
            indentation_++;

        return *this;
    }

private:
    UnderlyingStreamT* stream_;
    int indentation_;
};

#endif // BEAUTY_STREAM_H_INCLUDED
