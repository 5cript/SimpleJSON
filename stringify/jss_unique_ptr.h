#ifndef JSS_UNIQUE_PTR_H_INCLUDED
#define JSS_UNIQUE_PTR_H_INCLUDED

#include "jss_core.h"
#include "../utility/polymorphy.h"

#include <memory>

namespace JSON
{
    namespace internal
    {
        template <typename T, bool IsClass, bool IsPolymorphic>
        struct stringify_call_chooser
        {
        };

        template <typename T>
        struct stringify_call_chooser <T, true, false>
        {
            static void exec(std::ostream& stream, const std::string& name, T const& value, StringificationOptions const& options)
            {
                value->stringify(stream, options);
            }
        };

        template <typename T>
        struct stringify_call_chooser <T, true, true>
        {
            static void exec(std::ostream& stream, const std::string& name, T const& value, StringificationOptions const& options)
            {
                //value->stringify(stream, options);
                polydecls <typename T::element_type>::smart_pointer_set(value, stream, options);
            }
        };

        template <typename T, bool IsPolymorphic>
        struct stringify_call_chooser <T, false, IsPolymorphic>
        {
            static void exec(std::ostream& stream, const std::string& name, T const& value, StringificationOptions const& options)
            {
                stringify(stream, name, *value, options);
            }
        };
    }

    template <typename T, typename Deleter,
              typename = typename std::enable_if <
                Internal::can_stringify<T>::value ||
                !std::is_same <typename polydecls <T>::type, no_poly>::value
              >::type >
    std::ostream& stringify(std::ostream& stream, const std::string& name, std::unique_ptr<T, Deleter> const& value, StringificationOptions const& options = {})
    {
        if (!value)
            throw UniquePtrNullptrException{};

        if (options.in_object && !options.ignore_name)
            WRITE_NAME(stream);

        internal::stringify_call_chooser <
            typename std::decay<decltype(value)>::type,
            std::is_class <T>::value,
            !std::is_same <typename polydecls <T>::type, no_poly>::value
        >::exec(stream, name, value, options);
        return stream;
    }
}

#endif // JSS_UNIQUE_PTR_H_INCLUDED
