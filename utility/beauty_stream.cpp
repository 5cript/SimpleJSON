#include "beauty_stream.h"

BeautifiedStreamWrapper::BeautifiedStreamWrapper()
    : indentation_(0)
    , nestingStack_()
{
    nestingStack_.push(NestingState::IN_CLASS);
}
