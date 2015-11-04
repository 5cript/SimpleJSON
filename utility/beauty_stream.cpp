#include "beauty_stream.h"

namespace JSON
{
    BeautifiedStreamWrapper::BeautifiedStreamWrapper()
        : indentation_(0)
        , nestingStack_()
    {
        nestingStack_.push(NestingState::IN_CLASS);
    }
}
