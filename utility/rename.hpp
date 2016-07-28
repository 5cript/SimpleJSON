#pragma once

#include "../stringify/jss_core.hpp"
#include "../stringify/jss_object.hpp"

#include "../parse/jsd_core.hpp"
#include "../parse/jsd_object.hpp"

#include "meta_util.hpp"

#include <string>
#include <utility>
#include <type_traits>

namespace JSON
{
    template <typename T, typename Name>
    class rename
    {
    public:
        using type = T;
        using name = Name;

        operator type&()
        {
            return objectValue_;
        }

        operator type() const
        {
            return objectValue_;
        }

        type getValue() const
        {
            return objectValue_;
        }

        type& getValue()
        {
            return objectValue_;
        }

        void setValue(type const& objectValue) const
        {
            objectValue_ = objectValue;
        }

        rename <T, Name>& operator=(type const& objectValue)
        {
            objectValue_ = objectValue;
            return *this;
        }

        rename <T, Name>& operator=(type&& objectValue)
        {
            objectValue_ = objectValue;
            return *this;
        }

        template <typename OtherName>
        rename <T, Name>& operator=(rename <T, OtherName> const& other)
        {
            if (this == &other)
                return *this;

            objectValue_ = other.objectValue_;
            return *this;
        }

        template <typename OtherName>
        rename <T, Name>& operator=(rename <T, OtherName>&& other)
        {
            objectValue_ = other.objectValue_;
            return *this;
        }

        template <typename OtherName>
        rename(rename <T, OtherName> const& other)
            : objectValue_(other.objectValue_)
        {
        }

        template <typename OtherName>
        rename(rename <T, OtherName>&& other)
            : objectValue_(std::move(other.objectValue_))
        {
        }

        rename(type objectValue)
            : objectValue_(std::move(objectValue))
        {
        }

        template <typename U = type>
        rename(typename std::enable_if <std::is_default_constructible <U>::value>::type* = nullptr)
            : objectValue_()
        {

        }

        ~rename() = default;

        constexpr static const char* getName()
        {
            return name::c_str;
        }

        /*
        std::ostream& stringify(std::ostream& stream, StringificationOptions options) const
        {
            return JSON::stringify(stream, std::string(name::c_str), objectValue_, options);
        }
        */

    private:
        type objectValue_;
    };

    template <typename T>
    struct is_renamed
    {
        enum {
            value = false
        };
    };

    template <typename T, typename Name>
    struct is_renamed <rename <T, Name>>
    {
        enum {
            value = true
        };
    };
}
