#pragma once

#include "../stringify/jss_object.hpp"
#include "../parse/jsd_core.hpp"

#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>

/**
 *  Provides a wrapper called Base64Binary for use in classes instead of std::vector <char> etc.
 *  It is meant to compress binary data down.
 *
 *  And it is only meant for that, it does not produce correct output if shoved into stringify itself.
 */

namespace JSON
{
    template <typename CharType = char, template <typename...> class ContainerT = std::vector, typename... Dummys>
    void encodeBase64(std::ostream& stream, ContainerT <CharType, Dummys...> const& bytes);
    template <typename CharType = char, template <typename...> class ContainerT = std::vector, typename... Dummys>
    void decodeBase64(std::string const& input, ContainerT <CharType, Dummys...>& bytes);

    template <typename ContainerT>
    struct Base64Binary
    {
    protected:
        ContainerT binary_;

    public:

		using value_type		= typename ContainerT::value_type;
		using allocator_type	= typename ContainerT::allocator_type;
		using reference			= typename ContainerT::reference;
		using const_reference	= typename ContainerT::const_reference;
		using pointer			= typename ContainerT::pointer;
		using const_pointer		= typename ContainerT::const_pointer;
		using iterator			= typename ContainerT::iterator;
		using const_iterator	= typename ContainerT::const_iterator;
		using reverse_iterator	= typename ContainerT::reverse_iterator;
		using const_reverse_iterator = typename ContainerT::const_reverse_iterator;
		using difference_type	= typename ContainerT::difference_type;
		using size_type			= typename ContainerT::size_type;

        ContainerT& get() { return binary_; }

		Base64Binary() = default;
		virtual ~Base64Binary() = default;

        explicit Base64Binary(ContainerT container)
            : binary_(std::move(container))
        { }

        /**
         *  This constructor does stop on the null terminator '\0' (exclusive).
         */
        Base64Binary(const value_type* init)
            : binary_()
        {
            for (auto const* c = init; *c != '\0'; ++c)
                binary_.push_back(*c);
        }

        /**
         *  Inserts the container contents into a string.
         *
         *  @return A string from the binary data.
         */
        std::basic_string <value_type> toString() const
        {
            return {std::begin(binary_), std::end(binary_)};
        }

        Base64Binary& operator=(ContainerT const& container)
        {
            binary_ = container;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& ostr, Base64Binary const& bb)
        {
            ostr << bb.binary_;
            return ostr;
        }

        Base64Binary& operator=(const value_type* str)
        {
            binary_.clear();
            for (auto const* c = str; *c != '\0'; ++c)
                binary_.push_back(*c);
            return *this;
        }

        operator ContainerT&() { return binary_; }

        iterator begin() { return binary_.begin(); }
        iterator end() { return binary_.end(); }
        const_iterator cbegin() const { return binary_.cbegin(); }
        const_iterator cend() const { return binary_.cend(); }
        const_iterator begin() const { return binary_.begin(); }
        const_iterator end() const { return binary_.end(); }

		reference front() { return binary_.front(); }
		const_reference front() const { return binary_.front(); }
		reference back() { return binary_.back(); }
		const_reference back() const { return binary_.back(); }

		reference operator[] (size_type n) { return binary_[n]; }
		const_reference operator[] (size_type n) const { return binary_[n]; }
		reference at (size_type n) { return binary_.at(n); }
		const_reference at (size_type n) const { return binary_.at(n); }
		value_type* data() noexcept { return binary_.data(); }
		const value_type* data() const noexcept { return binary_.data(); }

		size_type size() const { return binary_.size(); }
		size_type max_size() const noexcept { return binary_.max_size(); }
		bool empty() const { return binary_.empty(); }

		void push_back(value_type const& v) { binary_.push_back(v); }
		void pop_back() { binary_.pop_back(); }
		void clear() noexcept { binary_.clear(); }
		void resize (size_type n) { binary_.resize(n); }
		void resize (size_type n, const value_type& val) { binary_.resize(n, val); }

        std::ostream& stringify(std::ostream& stream, StringificationOptions const& = {}) const
        {
            stream << "\"";
            encodeBase64(stream, binary_);
            stream << "\"";
            return stream;
        }

        void parse(std::string const& name, PropertyTree const& tree, ParsingOptions const& = {})
        {
            std::string str = tree.tree.get<std::string>(name);
            decodeBase64(str, binary_);
        }
    };

    template <typename... List>
    using Base64 = Base64Binary<List...>;
}

namespace JSON
{
    template <typename CharType, template <typename...> class ContainerT, typename... Dummys>
    void encodeBase64(std::ostream& stream, ContainerT <CharType, Dummys...> const& bytes)
    {
		static CharType const table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

        std::size_t b;
        for (std::size_t i = 0; i < bytes.size(); i += 3)
        {
            b = (bytes[i] & 0xFC) >> 2;
            stream << table [b];
            b = (bytes[i] & 0x03) << 4;

            if (i + 1 < bytes.size())
            {
                b |= (bytes[i + 1] & 0xF0) >> 4;
                stream << table [b];
                b = (bytes[i + 1] & 0x0F) << 2;

                if (i + 2 < bytes.size())
                {
                    b |= (bytes[i + 2] & 0xC0) >> 6;
                    stream << table [b];
                    b = bytes[i + 2] & 0x3F;
                    stream << table [b];
                }
                else
                {
                    stream << table [b];
                    stream << '=';
                }
            }
            else
            {
                stream << table [b];
                stream << "==";
            }
        }
    }

    template <typename CharType, template <typename...> class ContainerT, typename... Dummys>
    void decodeBase64(std::string const& input, ContainerT <CharType, Dummys...>& bytes)
    {
		// static CharType const table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

        bytes.clear();

        if (input.empty())
            return;

        if (input.length() % 4 != 0)    {
            throw std::invalid_argument ("input does not have correct size for base64");
        }

        std::size_t size = (input.length() * 3) / 4;
        if (*input.rbegin() == '=')
            size--;
        if (*(input.rbegin() + 1) == '=')
            size--;

        bytes.resize(size);

        auto backwardsTable = [](int c) -> int {
            if (c >= (int)'A' && c <= (int)'Z')
                return c - 'A';
            if (c >= (int)'a' && c <= (int)'z')
                return c - 'a' + 26;
            if (c >= (int)'0' && c <= (int)'9')
                return c - '0' + 52;
            if (c == '+')
                return 62;
            if (c == '/')
                return 63;
            if (c == '=')
                return 64;
            else
                throw std::invalid_argument ("input contains characters that are not base64");
            return 0;
        };

        int j = 0;
        int b[4];
        for (std::size_t i = 0; i < input.length(); i += 4)
        {
            b[0] = backwardsTable(input[i]);
            b[1] = backwardsTable(input[i + 1]);
            b[2] = backwardsTable(input[i + 2]);
            b[3] = backwardsTable(input[i + 3]);
            bytes[j++] = (CharType) ((b[0] << 2) | (b[1] >> 4));
            if (b[2] < 64)
            {
                bytes[j++] = (CharType) ((b[1] << 4) | (b[2] >> 2));
                if (b[3] < 64)
                {
                    bytes[j++] = (CharType) ((b[2] << 6) | b[3]);
                }
            }
        }
    }
}
