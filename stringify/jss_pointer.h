#ifndef JSS_POINTER_H_INCLUDED
#define JSS_POINTER_H_INCLUDED

#include "jss_core.h"
#include "jss_check.h"
#include "integer_of_size.h"

namespace JSON
{
    // pure object pointers:
    template <typename T>
    std::ostream& stringify(std::ostream& stream, std::string const& name, T ptr, StringificationOptions const& options = DEFAULT_OPTIONS,
                               typename std::enable_if <
                                  ( std::is_pointer<T>::value || std::is_member_object_pointer<T>::value )
                                  && !std::is_function<T>::value && !std::is_member_function_pointer<T>::value
                                  && !std::is_array<T>::value && Internal::can_stringify<decltype(*ptr)>::value
                               >::type* = nullptr)
    {
        switch (options.ptr_behaviour)
        {
            case (PointerHandling::IGNORE_POINTERS):
            {
                // IGNORE_POINTERS
            }
            case (PointerHandling::DEREFERENCE):
            {
                stringify(stream, name, *ptr, options);
            }
            case (PointerHandling::ADDRESS):
            {
                WRITE_NAME(stream);
                APPLY_IO_MANIPULATERS(stream);
                stream << reinterpret_cast <uint_of_size<sizeof(void*)>::type> (ptr);
            }
            default: {};
        }
        return stream;
    }

    std::ostream& stringify(std::ostream& stream, std::string const& name, std::nullptr_t ptr, StringificationOptions const& options = DEFAULT_OPTIONS);
}

#endif // JSS_POINTER_H_INCLUDED
