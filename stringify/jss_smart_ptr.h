#pragma once

namespace JSON
{
    namespace internal
    {
        template <typename T, bool IsClass, bool IsPolymorphic>
        struct smart_pointer_stringifier
        {
        };

        template <typename T>
        struct smart_pointer_stringifier <T, true, false>
        {
            static void exec(std::ostream& stream, const std::string& name, T const& value, StringificationOptions const& options)
            {
                value->stringify(stream, options);
            }
        };

        template <typename T>
        struct smart_pointer_stringifier <T, true, true>
        {
            static void exec(std::ostream& stream, const std::string& name, T const& value, StringificationOptions const& options)
            {
                //value->stringify(stream, options);
                polydecls <typename T::element_type>::smart_pointer_set(value, stream, options);
            }
        };

        template <typename T, bool IsPolymorphic>
        struct smart_pointer_stringifier <T, false, IsPolymorphic>
        {
            static void exec(std::ostream& stream, const std::string& name, T const& value, StringificationOptions const& options)
            {
                stringify(stream, name, *value, options);
            }
        };

        template <typename T>
        std::ostream& stringify_smart_ptr(std::ostream& stream, const std::string& name, T const& value, StringificationOptions const& options = {})
        {
            if (options.in_object && !options.ignore_name)
                WRITE_NAME(stream);

            using element_type = typename std::decay<decltype(value)>::type::element_type;

            internal::smart_pointer_stringifier <
                typename std::decay<decltype(value)>::type,
                std::is_class <element_type>::value,
                !std::is_same <element_type, no_poly>::value
            >::exec(stream, name, value, options);
            return stream;
        }
    }
}
