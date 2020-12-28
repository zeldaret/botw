#include "Game/AI/Action/actionGrabLeftWalk.h"

namespace uking::action {

GrabLeftWalk::GrabLeftWalk(const InitArg& arg) : MoveBase(arg) {}

void GrabLeftWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
}

}  // namespace uking::action
