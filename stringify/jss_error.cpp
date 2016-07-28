#include "jss_error.hpp"

using namespace JSON;

const char* BaseException::what() const noexcept
{
    return name();
}
const char * BaseException::name() const noexcept
{
    return "JSON_BaseException";
}
int BaseException::code() const noexcept
{
    return code_;
}
std::string BaseException::message() const noexcept
{
    return message_;
}
BaseException::BaseException()
    : code_(0)
    , message_("")
{

}
BaseException::BaseException(int code)
    : code_(code)
    , message_("")
{

}
BaseException::BaseException(std::string message)
    : code_(0)
    , message_(std::move(message))
{

}
BaseException::BaseException(std::string message, int code)
    : code_(code)
    , message_(std::move(message))
{

}
