#include "beauty_stream.hpp"

namespace JSON
{
    BeautifiedStreamWrapper::BeautifiedStreamWrapper()
        : indentation_(0)
        , escape_(false)
        , disabled_(false)
        , nestingStack_()
    {
        nestingStack_.push(NestingState::IN_CLASS);
    }
}
