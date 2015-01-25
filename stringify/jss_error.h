#ifndef JSS_ERROR_H_INCLUDED
#define JSS_ERROR_H_INCLUDED

#include <exception>
#include <string>

namespace JSON
{
#ifdef _MSC_VER
#if _MSC_VER <= 1800
#define noexcept throw()
#endif
#endif

    class BaseException : public std::exception
    {
    public:
        virtual const char* what() const noexcept;
        virtual const char * name() const noexcept;
        int code() const noexcept;
        std::string message() const noexcept;

        BaseException();
        BaseException(int code);
        BaseException(std::string message);
        BaseException(std::string message, int code);

        // defaults
        BaseException(BaseException const&) = default;
        BaseException& operator=(BaseException const&) = default;
        virtual ~BaseException() = default;

    private:
        int code_;
        std::string message_;
    };

    #define REGISTER_EXCEPTION(cname, base)             \
    class cname : public base                           \
    {                                                   \
    public:                                             \
        virtual const char* what() const noexcept       \
        {                                               \
            return name();                              \
        }                                               \
        virtual const char* name() const noexcept       \
        {                                               \
            return "JSON_"#cname;                       \
        }                                               \
        cname() : base() {}                             \
        cname(int code) : base(code) {}                 \
        cname(std::string message) : base(message) {}   \
        cname(std::string message, int code)            \
            : base(message, code) {}                    \
    }
    // MAKRO END

    REGISTER_EXCEPTION(BadStringException, BaseException);
    REGISTER_EXCEPTION(NullptrException, BaseException);
    REGISTER_EXCEPTION(WeakPtrExpiredException, BaseException);
    REGISTER_EXCEPTION(SharedPtrNullptrException, BaseException);
    REGISTER_EXCEPTION(UniquePtrNullptrException, BaseException);

    #undef REGISTER_EXCEPTION
}

#endif // JSS_ERROR_H_INCLUDED
