#include "Game/AI/Action/actionWait.h"

namespace uking::action {

Wait::Wait(const InitArg& arg) : WaitBase(arg) {}

void Wait::enter_(ksys::act::ai::InlineParamPack* params) {
    WaitBase::enter_(params);
}

}  // namespace uking::action
