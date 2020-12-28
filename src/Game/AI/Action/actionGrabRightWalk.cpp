#include "Game/AI/Action/actionGrabRightWalk.h"

namespace uking::action {

GrabRightWalk::GrabRightWalk(const InitArg& arg) : MoveBase(arg) {}

void GrabRightWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
}

}  // namespace uking::action
