#include "jss_pointer.hpp"

namespace JSON
{
    std::ostream& stringify(std::ostream& stream, std::string const& name, std::nullptr_t, StringificationOptions const& options)
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
                SJSON_WRITE_NAME(stream);
                stream << 0u;
                return stream;
            }
            default: {}
        }
        return stream;
    }
}
