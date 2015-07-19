#include "jss_pointer.h"

namespace JSON
{
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::nullptr_t ptr, StringificationOptions const& options)
    {
        switch (options.ptr_behaviour)
        {
            case (PointerHandling::IGNORE_POINTERS):
            {
            }
            case (PointerHandling::DEREFERENCE):
            {
                throw NullptrException{};
            }
            case (PointerHandling::ADDRESS):
            {
                WRITE_NAME(stream);
                APPLY_IO_MANIPULATERS(stream);
                stream << reinterpret_cast <uint_of_size<sizeof(void*)>::type> (ptr);
                return stream;
            }
            default: {}
        }
        return stream;
    }
}
