#include "jss_pointer.h"

namespace JSON
{
    std::string js_stringify(std::string const& name, std::nullptr_t ptr, StringificationOptions const& options)
    {
        switch (options.ptr_behaviour)
        {
            case (PointerHandling::IGNORE):
            {
                return {};
            }
            case (PointerHandling::DEREFERENCE):
            {
                throw NullptrException{};
            }
            case (PointerHandling::ADDRESS):
            {
                std::stringstream sstr;
                WRITE_NAME(sstr);
                APPLY_IO_MANIPULATERS(sstr);
                sstr << reinterpret_cast <uint_of_size<sizeof(void*)>::type> (ptr);
                return sstr.str();
            }
            default:
                return {};
        }
    }
}
