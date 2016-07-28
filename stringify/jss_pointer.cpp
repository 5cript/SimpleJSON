#include "jss_pointer.hpp"

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
                stream << reinterpret_cast <uint_of_size<sizeof(void*)>::type> (ptr);
                return stream;
            }
            default: {}
        }
        return stream;
    }
}
