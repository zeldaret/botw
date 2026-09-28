#include "Game/Actor/Action/actionGuardLoop.h"

namespace uking::action {

GuardLoop::GuardLoop(const InitArg& arg) : StopBase(arg) {}

void GuardLoop::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

}  // namespace uking::action
