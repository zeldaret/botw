#include "Game/AI/Action/actionGuardLoop.h"

namespace uking::action {

GuardLoop::GuardLoop(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

void GuardLoop::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

}  // namespace uking::action
